#include "Move.h"

Move::Move(Character* character, Node* move_node)
{
    this->character = character;
    vector<Node*> frame_nodes = move_node->getNodesByName("Frame");
    for(int i=0;i<(int)frame_nodes.size();i++)
    {
        Frame* frame = new Frame(character, this, frame_nodes[i]);
        this->frames.push_back(frame);
    }
    this->restart();
}

void Move::draw(int x, int y, bool flipped)
{
    Frame* frame = frames[this->current_frame];
    frame->draw(x, y, flipped);
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
      frame->logic();
    }
}

void Move::restart()
{
    tick = 0;
    current_frame = 0;
    finished = false;
    Frame* frame = frames[this->current_frame];
    frame->restart();
}

bool Move::isFinished()
{
    return finished;
}

Frame* Move::getCurrentFrame()
{
    return frames[this->current_frame];
}
