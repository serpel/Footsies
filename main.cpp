#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include <string>

#include "Rosalila/Rosalila.h"
#include "RosalilaFootsies/Footsies.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  rosalila()->init();
  Footsies *footsies = new Footsies("Footsies1", "Footsies2");
  footsies->gameLoop();

/*
  vector<Node*> character_nodes = rosalila()->parser->getNodes(assets_directory+"config.xml")->getNodeByName("Characters")->getNodesByName("Character");


  for(int i=0;i<(int)character_nodes.size();i++)
    cout<<character_nodes[i]->attributes["name"]<<endl;

  Image* background = rosalila()->graphics->getTexture(assets_directory+"menu/character_select_bg.png");
  while(true)
  {
    rosalila()->graphics->draw2DImage
    (   background,
        background->getWidth(),background->getHeight(),
        0,0,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow());

    if(rosalila()->receiver->isKeyPressed(SDLK_RETURN))
    {
      Footsies *footsies = new Footsies();
      footsies->gameLoop();
    }

    rosalila()->update();
  }*/
  return 0;
}
