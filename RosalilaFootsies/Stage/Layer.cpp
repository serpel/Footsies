#include "Layer.h"

Layer::Layer(Stage* stage, Node* layer_node)
{
  this->stage = stage;
  this->current_image = 0;
  this->current_image_frame = 0;
  this->frame = 0;

  this->x = atof(layer_node->attributes["x"].c_str());
  this->y = atof(layer_node->attributes["y"].c_str());
  this->velocity_x = atof(layer_node->attributes["velocity_x"].c_str());
  this->velocity_y = atof(layer_node->attributes["velocity_y"].c_str());
  this->reset_at = atoi(layer_node->attributes["reset_at"].c_str());
  this->original_x = x;
  this->original_y = y;

  vector<Node*> image_nodes = layer_node->getNodesByName("Image");
  for(int i=0;i<(int)image_nodes.size();i++)
  {
    images.push_back(rosalila()->graphics->getTexture(assets_directory+"stages/" + this->stage->name + "/" +image_nodes[i]->attributes["path"]));
    if(image_nodes[i]->attributes.find("duration")!=image_nodes[i]->attributes.end())
      image_durations.push_back(atoi(image_nodes[i]->attributes["duration"].c_str()));
    else
      image_durations.push_back(0);
  }
}

void Layer::draw()
{
  rosalila()->graphics->draw2DImage
  (   images[current_image],
      images[current_image]->getWidth(),images[current_image]->getHeight(),
      this->x,this->y,
      1.0,
      0.0,
      false,
      0,0,
      Color(255,255,255,255),
      0,0,
      false,
      FlatShadow());
}

void Layer::logic()
{
  this->x += velocity_x;
  this->y += velocity_y;

  current_image_frame++;
  if(current_image_frame >= image_durations[current_image])
  {
    current_image_frame = 0;
    current_image++;
    if(current_image>=(int)images.size())
      current_image=0;
  }
  if(frame == reset_at)
  {
    this->x = this->original_x;
    this->y = this->original_y;
    this->frame = 0;
    this->current_image = 0;
    this->current_image_frame = 0;
  }
  frame++;
}
