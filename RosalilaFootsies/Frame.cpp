#include "Frame.h"

Frame::Frame(Character*character, Move* move, Node* frame_node)
{
    this->character = character;
    this->move = move;

    this->restart();

    this->image = rosalila()->graphics->getTexture(assets_directory+"character/" + this->character->name + "/" +frame_node->attributes["image"]);

    Node* hitboxes_node = frame_node->getNodeByName("Hitboxes");
    Node* hurtboxes_node = frame_node->getNodeByName("Hurtboxes");

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
            this->hitboxes.push_back(new Hitbox(x,y,width,height,angle) );
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
            this->hurtboxes.push_back(new Hitbox(x,y,width,height,angle) );
        }
   }

   this->duration = atoi(frame_node->attributes["duration"].c_str());

   velocity_x_changed = false;
   if(frame_node->hasAttribute("velocity_x"))
   {
      velocity_x_changed = true;
      this->velocity_x = atoi(frame_node->attributes["velocity_x"].c_str());
   }

   velocity_y_changed = false;
   if(frame_node->hasAttribute("velocity_y"))
   {
      velocity_y_changed = true;
      this->velocity_y = atoi(frame_node->attributes["velocity_y"].c_str());
   }

   acceleration_x_changed = false;
   if(frame_node->hasAttribute("acceleration_x"))
   {
      acceleration_x_changed = true;
      this->acceleration_x = atoi(frame_node->attributes["acceleration_x"].c_str());
   }

   acceleration_y_changed = false;
   if(frame_node->hasAttribute("acceleration_y"))
   {
      acceleration_y_changed = true;
      this->acceleration_y = atoi(frame_node->attributes["acceleration_y"].c_str());
   }
}

void Frame::draw(int x, int y, bool flipped)
{
    rosalila()->graphics->draw2DImage
    (   image,
        image->getWidth(),image->getHeight(),
        x-image->getWidth()/2,620-image->getHeight() - y,
        1.0,
        0.0,
        flipped,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow());

    if(rosalila()->receiver->isKeyDown('h'))
    if(!flipped)
    {
        for(int i=0;i< (int)hitboxes.size();i++)
            rosalila()->graphics->drawRectangle(hitboxes[i]->x + x,620-hitboxes[i]->y,
                                              hitboxes[i]->width,hitboxes[i]->height,0,
                                              255,0,0,128,true);

        for(int i=0;i< (int)hurtboxes.size();i++)
          rosalila()->graphics->drawRectangle(hurtboxes[i]->x + x,620-hurtboxes[i]->y,
                                              hurtboxes[i]->width,hurtboxes[i]->height,0,
                                              0,0,255,128,true);
    }else
    {
        for(int i=0;i< (int)hitboxes.size();i++)
            rosalila()->graphics->drawRectangle(-hitboxes[i]->x - hitboxes[i]->width + x,620-hitboxes[i]->y,
                                              hitboxes[i]->width,hitboxes[i]->height,0,
                                              255,0,0,128,true);

        for(int i=0;i< (int)hurtboxes.size();i++)
          rosalila()->graphics->drawRectangle(-hurtboxes[i]->x - hurtboxes[i]->width + x,620-hurtboxes[i]->y,
                                              hurtboxes[i]->width,hurtboxes[i]->height,0,
                                              0,0,255,128,true);
    }
}

void Frame::logic()
{
    if(frame >= duration)
    {
        finished = true;
    }

    if(frame==0)
    {
      if(velocity_x_changed)
          character->velocity_x = this->velocity_x;
      if(velocity_y_changed)
          character->velocity_y = this->velocity_y;
      if(acceleration_x_changed)
          character->acceleration_x = this->acceleration_x;
      if(acceleration_y_changed)
          character->acceleration_y = this->acceleration_y;
    }

    frame++;
}

void Frame::restart()
{
    frame = 0;
    finished = false;
}

bool Frame::isFinished()
{
    return finished;
}
