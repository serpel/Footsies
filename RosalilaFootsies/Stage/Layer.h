#ifndef LAYER_H
#define LAYER_H

#include "../../Rosalila/Rosalila.h"
#include "Stage.h"

class Stage;

class Layer
{
public:
  vector<Image*> images;
  vector<int> image_durations;
  int frame;
  double x;
  double y;
  double velocity_x;
  double velocity_y;
  double original_x;
  double original_y;
  int reset_at;
  Stage* stage;
  int current_image;
  int current_image_frame;
  Layer(Stage* stage, Node* layer_node);
  void draw();
  void logic();
};

#endif
