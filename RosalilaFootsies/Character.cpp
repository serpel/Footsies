#include "Character.h"

Character::Character(int player, int x)
{

    Node* moves_node = rosalila()->parser->getNodes(assets_directory+"character/moves.xml");
    vector<Node*> move_nodes = moves_node->getNodesByName("Move");
    for(int i=0; i< (int)move_nodes.size(); i++)
    {
        moves[move_nodes[i]->attributes["name"]] = new Move(this,move_nodes[i]);
    }

    this->current_state = "idle";
    this->frame = 0;
    this->animation_frame = 0;
    this->x = x;
    button_up = false;

    opponent = NULL;
    this->player = player;
    game_started = false;
}

void Character::draw()
{
    Move* current_move = moves[this->current_state];
    current_move->draw(this->x, this->isFlipped());
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
        bool punch_pressed = rosalila()->receiver->isJoyDown(1,player);

        if(this->isFlipped())
        {
            bool temp = left_pressed;
            left_pressed = right_pressed;
            right_pressed = temp;
        }

        if(!punch_pressed)
            button_up = true;

        bool none_pressed = !left_pressed && !right_pressed && !punch_pressed;


        if(none_pressed && 
                (this->current_state == "walk_back" || this->current_state == "walk_forward") )
            cancel("idle");

        if(left_pressed && 
                (this->current_state == "idle" || this->current_state == "walk_forward") )
            cancel("walk_back");

        if(right_pressed && 
                (this->current_state == "idle" || this->current_state == "walk_back") )
            cancel("walk_forward");

        if(button_up && punch_pressed && this->current_state != "punch" &&
                (this->current_state == "idle" || this->current_state == "walk_back" || this->current_state == "walk_forward") )
        {
            button_up = false;
            cancel("punch");
        }
    }

    Move* current_move = moves[this->current_state];
    current_move->logic();
}

void Character::cancel(string new_state)
{
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
