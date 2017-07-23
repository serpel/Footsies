#include "Stage.h"

Stage::Stage(string name)
{
  this->name = name;
  Node* config_node = rosalila()->parser->getNodes(assets_directory+"stages/" + this->name + "/config.xml");
  vector<Node*> layer_nodes = config_node->getNodeByName("Layers")->getNodesByName("Layer");
  for(int i=0;i<(int)layer_nodes.size();i++)
  {
    layers.push_back(new Layer(this,layer_nodes[i]));
  }
}

void Stage::draw()
{
  for(int i=0;i<(int)layers.size();i++)
  {
    layers[i]->draw();
  }
}

void Stage::logic()
{
  for(int i=0;i<(int)layers.size();i++)
  {
    layers[i]->logic();
  }
}
