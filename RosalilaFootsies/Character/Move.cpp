#include "Move.h"

Move::Move(Character* character, Node* move_node)
{
  this->character = character;

  if(move_node->hasAttribute("sound"))
  {
    string sound_name = character->name + "#" + move_node->attributes["name"];
    string sound_path = assets_directory + "character/" + character->name + "/" + move_node->attributes["sound"];
    rosalila()->sound->addSound(sound_name, sound_path);
  }
  vector<Node*> frame_nodes = move_node->getNodeByName("Frames")->getNodesByName("Frame");
  for(int i=0;i<(int)frame_nodes.size();i++)
  {
      Frame* frame = new Frame(character, this, frame_nodes[i]);
      this->frames.push_back(frame);
  }

  if(move_node->getNodeByName("Cancels"))
  {
    vector<Node*> cancel_nodes = move_node->getNodeByName("Cancels")->getNodesByName("Cancel");
    for(int i=0;i<(int)cancel_nodes.size();i++)
    {
        this->cancels.push_back(cancel_nodes[i]->attributes["move"]);
    }
  }

  if(move_node->getNodeByName("Inputs"))
  {
    vector<Node*> input_nodes = move_node->getNodeByName("Inputs")->getNodesByName("Input");
    for(int i=0;i<(int)input_nodes.size();i++)
    {
      vector<Node*> button_nodes = input_nodes[0]->getNodesByName("Button");
      vector<string> input;
      for(int i=0;i<(int)button_nodes.size();i++)
      {
        input.push_back(button_nodes[i]->attributes["name"]);
      }
      inputs.push_back(input);
    }
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

bool Move::canCancel(string move)
{
  for(int i=0; i<(int)cancels.size();i++)
  {
    if(cancels[i]==move)
      return true;
  }
  return false;
}

bool Move::inputIsInBuffer()
{
  for(int i=0;i<(int)inputs.size();i++)
  {
    list<string>::iterator current_move_button = character->input_buffer.begin();
    bool input_found = true;
    for(int j=0;j<(int)inputs[i].size();j++)
    {
      if(inputs[i][j].size()!=(*current_move_button).size())
      {
        input_found = false;
        break;
      }
      for(int k=0;k<(int)inputs[i][j].size();k++)
      {
        if(inputs[i][j][k]=='*')
          continue;
        if(inputs[i][j][k]!=(*current_move_button)[k])
        {
          input_found = false;
          break;
        }
      }
      current_move_button++;
    }
    if(input_found)
      return true;
  }
  return false;
}

Frame* Move::getCurrentFrame()
{
  return frames[this->current_frame];
}
