#include "Move.h"

Move::Move(Character* character, Node* move_node)
{
    this->character = character;
    velocity_x = 0;
    if(move_node->hasAttribute("velocity_x"))
    {
        velocity_x = atoi(move_node->attributes["velocity_x"].c_str());
    }
    vector<Node*> frame_nodes = move_node->getNodesByName("Frame");
    for(int i=0;i<(int)frame_nodes.size();i++)
    {
         Image* image = rosalila()->graphics->getTexture(assets_directory+frame_nodes[i]->attributes["image"]);
         vector<Hitbox*> hitboxes;
         vector<Hitbox*> hurtboxes;

         Node* hitboxes_node = frame_nodes[i]->getNodeByName("Hitboxes");
         Node* hurtboxes_node = frame_nodes[i]->getNodeByName("Hurtboxes");

         if(hitboxes_node)
         {
             vector<Node*> hitbox_nodes = hitboxes_node->getNodesByName("Hitbox");
             for(int j=0;j< (int)hitbox_nodes.size();j++)
             {
                 int x = atoi(hitbox_nodes[j]->attributes["x"].c_str());
                 int y = atoi(hitbox_nodes[j]->attributes["y"].c_str());
                 int width = atoi(hitbox_nodes[j]->attributes["width"].c_str());
                 int height = atoi(hitbox_nodes[j]->attributes["height"].c_str());
                 int angle = atoi(hitbox_nodes[j]->attributes["angle"].c_str());
                 hitboxes.push_back(new Hitbox(x,y,width,height,angle) );
             }
         }

         if(hurtboxes_node)
         {
             vector<Node*> hurtbox_nodes = hurtboxes_node->getNodesByName("Hurtbox");

             for(int j=0;j< (int)hurtbox_nodes.size();j++)
             {
                 int x = atoi(hurtbox_nodes[j]->attributes["x"].c_str());
                 int y = atoi(hurtbox_nodes[j]->attributes["y"].c_str());
                 int width = atoi(hurtbox_nodes[j]->attributes["width"].c_str());
                 int height = atoi(hurtbox_nodes[j]->attributes["height"].c_str());
                 int angle = atoi(hurtbox_nodes[j]->attributes["angle"].c_str());
                 hurtboxes.push_back(new Hitbox(x,y,width,height,angle) );
             }
        }

        Frame* frame = new Frame(image,hitboxes,hurtboxes,atoi(frame_nodes[i]->attributes["duration"].c_str()) );
        this->frames.push_back(frame);
    }
    this->restart();
}

void Move::draw(int x, bool flipped)
{
    Frame* frame = frames[this->current_frame];
    frame->draw(x, flipped);
}

void Move::logic()
{
    tick++;

    Frame* frame = frames[this->current_frame];
    frame->logic();

    if(frame->isFinished())
    {
      this->current_frame++;
      if(current_frame>=(int)frames.size())
			{
          current_frame=0;
          finished=true;
      }
      frame = frames[this->current_frame];
      frame->restart();
    }
    if(character->isFlipped())
      character->x -= velocity_x;
    else
      character->x += velocity_x;
}

void Move::restart()
{
    tick = 0;
    current_frame = 0;
    finished = false;
}

bool Move::isFinished()
{
    return finished;
}

Frame* Move::getCurrentFrame()
{
    return frames[this->current_frame];
}
