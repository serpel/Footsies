#include "Character.h"

Character::Character(int player, int x, bool is_bot)
{

    Node* config_node = rosalila()->parser->getNodes(assets_directory+"character/config.xml");
    vector<Node*> files_nodes = config_node->getNodeByName("MoveFiles")->getNodesByName("File");
    for(int i=0; i< (int)files_nodes.size(); i++)
    {
        Node* moves_node = rosalila()->parser->getNodes(assets_directory+"character/" + files_nodes[i]->attributes["path"]);
        vector<Node*> move_nodes = moves_node->getNodesByName("Move");
        for(int i=0; i< (int)move_nodes.size(); i++)
        {
            moves[move_nodes[i]->attributes["name"]] = new Move(this,move_nodes[i]);
        }
    }

    this->current_state = "idle";
    this->frame = 0;
    this->animation_frame = 0;
    this->x = x;
    this->y = 0;
    this->velocity_x = 0;
    this->velocity_y = 0;
    this->acceleration_x = 0;
    this->acceleration_y = 0;

    button_up = false;
    this->is_bot = is_bot;

    opponent = NULL;
    this->player = player;
    game_started = false;

    for(int i=0;i<20;i++)
      input_buffer.push_back("5");
}

void Character::draw()
{
    Move* current_move = moves[this->current_state];
    current_move->draw(this->x, this->y, this->isFlipped());
}

void Character::logic()
{
    if(game_started)
    {
        Move* previous_move = moves[this->current_state];
        if(previous_move->isFinished())
            cancel("idle");

        bool left_pressed = rosalila()->receiver->isJoyDown(-4,player);
        bool right_pressed = rosalila()->receiver->isJoyDown(-6,player);
        bool up_pressed = rosalila()->receiver->isJoyDown(-8,player);
        bool punch_pressed = rosalila()->receiver->isJoyDown(1,player);

        string input_pressed = "5";

        if(left_pressed)
          input_pressed = "4";
        if(right_pressed)
          input_pressed = "6";
        if(up_pressed)
          input_pressed = "8";


        if(is_bot)
        {
            int distance = abs(this->x-opponent->x);
            left_pressed = true;
            if(distance<231)
                punch_pressed=true;
        }else
        {
            left_pressed = rosalila()->receiver->isJoyDown(-4,player);
            right_pressed = rosalila()->receiver->isJoyDown(-6,player);
            punch_pressed = rosalila()->receiver->isJoyDown(1,player);
        }

        if(this->isFlipped())
        {
            bool temp = left_pressed;
            left_pressed = right_pressed;
            right_pressed = temp;
        }

        if(!punch_pressed)
            button_up = true;

        input_buffer.pop_back();
        input_buffer.push_front(input_pressed);

        bool none_pressed = !left_pressed && !right_pressed && !punch_pressed && !up_pressed;

        if(none_pressed && this->moves["idle"]->canCancel(this->current_state))
            cancel("idle");

        if(left_pressed && this->moves["walk_back"]->canCancel(this->current_state))
            cancel("walk_back");

        if(right_pressed && this->moves["walk_forward"]->canCancel(this->current_state))
            cancel("walk_forward");

        if(button_up && punch_pressed && this->current_state != "punch" && this->moves["punch"]->canCancel(this->current_state))
        {
            button_up = false;
            cancel("punch");
        }

        if(button_up && up_pressed && this->current_state != "punch" && this->moves["jump_forward"]->canCancel(this->current_state))
        {
            button_up = false;
            cancel("jump_forward");
        }

        velocity_x += acceleration_x;
        velocity_y += acceleration_y;

        int last_y = y;

        if(this->isFlipped())
            this->x -= velocity_x;
        else
            this->x += velocity_x;
        this->y += velocity_y;

        if(y<=0)
        {
          y = 0;
          acceleration_y = 0;
        }else
        {
          acceleration_y-=0.25;
        }

        if(last_y > 0 && y == 0)
        {
          cancel("idle");
        }
    }

    Move* current_move = moves[this->current_state];
    current_move->logic();
}

void Character::cancel(string new_state)
{
    this->velocity_x = 0;
    this->velocity_y = 0;
    this->current_state=new_state;
    Move* new_move = moves[current_state];
    new_move->restart();
}

bool Character::isFlipped()
{
    return opponent->x < this->x;
}

Move* Character::getCurrentMove()
{
    return moves[this->current_state];
}
