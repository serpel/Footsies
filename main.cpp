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

  Image* background = rosalila()->graphics->getTexture(assets_directory + "menu/character_select_bg.png");
  Image* cursor_player1 = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player1.png");
  Image* cursor_player2 = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player2.png");
  Image* cursor_player1_selected = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player1_selected.png");
  Image* cursor_player2_selected = rosalila()->graphics->getTexture(assets_directory + "menu/cursor_player2_selected.png");

  vector<string> character_directories = rosalila()->utility->getDirectoryNames(assets_directory + "character/");
  vector<Image*> portraits;

  for(int i=0; i<(int)character_directories.size(); i++)
    portraits.push_back(rosalila()->graphics->getTexture(assets_directory + "character/" + character_directories[i] + "/portrait.png"));

  int player1_cursor = 0;
  int player2_cursor = portraits.size()-1;
  int player1_selection = -1;
  int player2_selection = -1;

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

    for(int i=0; i<(int)portraits.size(); i++)
    {
      int x = i*500;
      int y = 0;

      rosalila()->graphics->draw2DImage
      (   portraits[i],
          portraits[i]->getWidth(),portraits[i]->getHeight(),
          x,y,
          1.0,
          0.0,
          false,
          0,0,
          Color(255,255,255,255),
          0,0,
          false,
          FlatShadow());

      if(rosalila()->receiver->isJoyPressed(-6,0) && player1_selection == -1)
      {
        player1_cursor++;
        if(player1_cursor >= (int)portraits.size())
          player1_cursor = 0;
      }

      if(rosalila()->receiver->isJoyPressed(-4,0) && player1_selection == -1)
      {
        player1_cursor--;
        if(player1_cursor < 0)
          player1_cursor = portraits.size()-1;
      }

      if(rosalila()->receiver->isJoyPressed(1,0))
      {
        player1_selection = player1_cursor;
      }


      if(rosalila()->receiver->isJoyPressed(-6,1) && player2_selection == -1)
      {
        player2_cursor++;
        if(player2_cursor >= (int)portraits.size())
          player2_cursor = 0;
      }

      if(rosalila()->receiver->isJoyPressed(-4,1) && player2_selection == -1)
      {
        player2_cursor--;
        if(player2_cursor < 0)
          player2_cursor = portraits.size()-1;
      }

      if(rosalila()->receiver->isJoyPressed(1,1))
      {
        player2_selection = player2_cursor;
      }

      if(player1_cursor == i)
      {
        if(player1_selection == -1)
          rosalila()->graphics->draw2DImage
          (   cursor_player1,
              cursor_player1->getWidth(),cursor_player1->getHeight(),
              x,y,
              1.0,
              0.0,
              false,
              0,0,
              Color(255,255,255,255),
              0,0,
              false,
              FlatShadow());
        else
          rosalila()->graphics->draw2DImage
          (   cursor_player1_selected,
              cursor_player1_selected->getWidth(),cursor_player1_selected->getHeight(),
              x,y,
              1.0,
              0.0,
              false,
              0,0,
              Color(255,255,255,255),
              0,0,
              false,
              FlatShadow());
      }

      if(player2_cursor == i)
      {
        if(player2_selection == -1)
          rosalila()->graphics->draw2DImage
          (   cursor_player2,
              cursor_player2->getWidth(),cursor_player2->getHeight(),
              x,y,
              1.0,
              0.0,
              false,
              0,0,
              Color(255,255,255,255),
              0,0,
              false,
              FlatShadow());
        else
          rosalila()->graphics->draw2DImage
          (   cursor_player2_selected,
              cursor_player2_selected->getWidth(),cursor_player2_selected->getHeight(),
              x,y,
              1.0,
              0.0,
              false,
              0,0,
              Color(255,255,255,255),
              0,0,
              false,
              FlatShadow());
      }
    }

    if(player1_selection != -1 && player2_selection != -1)
    {
      Footsies *footsies = new Footsies(character_directories[player1_selection], character_directories[player2_selection]);
      footsies->gameLoop();
    }

    rosalila()->update();
  }

  return 0;
}
