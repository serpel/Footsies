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
  vector< vector<Image*> > idle_animations;
  vector< vector<int> > idle_animation_durations;
  int player1_idle_animation_frame = 0;
  int player2_idle_animation_frame = 0;
  int player1_idle_animation_image = 0;
  int player2_idle_animation_image = 0;

  for(int i=0; i<(int)character_directories.size(); i++)
  {
    string directory_name = character_directories[i];
    portraits.push_back(rosalila()->graphics->getTexture(assets_directory + "character/" + directory_name + "/portrait.png"));

    Node* moves_node = rosalila()->parser->getNodes(assets_directory+"character/" + directory_name + "/displacement.xml");
    vector<Node*> move_nodes = moves_node->getNodesByName("Move");
    for(int i=0; i<(int)move_nodes.size(); i++)
    {
      if(move_nodes[i]->attributes["name"]=="idle")
      {
        vector<Node*> frames = move_nodes[i]->getNodeByName("Frames")->getNodesByName("Frame");
        vector<Image*> idle_animation;
        vector<int> durations;
        for(int i=0; i<(int)frames.size(); i++)
        {
          idle_animation.push_back(rosalila()->graphics->getTexture(assets_directory + "character/" + directory_name + "/" + frames[i]->attributes["image"]));
          durations.push_back(atoi(frames[i]->attributes["duration"].c_str()));
        }
        idle_animations.push_back(idle_animation);
        idle_animation_durations.push_back(durations);
      }
    }
  }

  int player1_cursor = 0;
  int player2_cursor = portraits.size()-1;
  int player1_selection = -1;
  int player2_selection = -1;

  TTF_Font* menu_font = NULL;

  string font_path = assets_directory+"misc/font.ttf";
  menu_font = TTF_OpenFont( font_path.c_str(), 28 );

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
      int x = i*120 + 372;
      int y = 90;

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
          FlatShadow()
      );

      if((rosalila()->receiver->isKeyPressed('d') && player1_selection == -1)
          || (rosalila()->receiver->isJoyPressed(-6,0) && player1_selection == -1))
      {
        player1_cursor++;
        if(player1_cursor >= (int)portraits.size())
           player1_cursor = 0;
        player1_idle_animation_frame = 0;
        player1_idle_animation_image = 0;
      }

      if((rosalila()->receiver->isKeyPressed('a') && player1_selection == -1)
        || (rosalila()->receiver->isJoyPressed(-4,0) && player1_selection == -1))
      {
        player1_cursor--;
        if(player1_cursor < 0)
          player1_cursor = portraits.size()-1;
        player1_idle_animation_frame = 0;
        player1_idle_animation_image = 0;
      }

      if((rosalila()->receiver->isKeyPressed('l') && player1_selection == -1)
        || (rosalila()->receiver->isJoyPressed(-6,1) && player2_selection == -1))
      {
        player2_cursor++;
        if(player2_cursor >= (int)portraits.size())
           player2_cursor = 0;
        player2_idle_animation_frame = 0;
        player2_idle_animation_image = 0;
      }

      if((rosalila()->receiver->isKeyPressed('j') && player1_selection == -1)
        || (rosalila()->receiver->isJoyPressed(-4,1) && player2_selection == -1))
      {
        player2_cursor--;
        if(player2_cursor < 0)
          player2_cursor = portraits.size()-1;
        player2_idle_animation_frame = 0;
        player2_idle_animation_image = 0;
      }


      if(rosalila()->receiver->isJoyPressed(1,0) || rosalila()->receiver->isKeyPressed('w'))
      {
        player1_selection = player1_cursor;
      }

      if(rosalila()->receiver->isKeyPressed('i') || rosalila()->receiver->isJoyPressed(1,1))
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
      Footsies *footsies = new Footsies(character_directories[player1_selection], character_directories[player2_selection],3);
      footsies->gameLoop();
      player1_selection = -1;
      player2_selection = -1;
    }

    player1_idle_animation_frame++;
    if(player1_idle_animation_frame >= idle_animation_durations[player1_cursor][player1_idle_animation_image])
    {
      player1_idle_animation_frame = 0;
      player1_idle_animation_image++;
      if(player1_idle_animation_image >= (int)idle_animations[player1_cursor].size())
      player1_idle_animation_image = 0;
    }

    player2_idle_animation_frame++;
    if(player2_idle_animation_frame >= idle_animation_durations[player2_cursor][player2_idle_animation_image])
    {
      player2_idle_animation_frame = 0;
      player2_idle_animation_image++;
      if(player2_idle_animation_image >= (int)idle_animations[player2_cursor].size())
        player2_idle_animation_image = 0;
    }

    Image* player1_idle_image = idle_animations[player1_cursor][player1_idle_animation_image];
    rosalila()->graphics->draw2DImage
    (   player1_idle_image,
        player1_idle_image->getWidth(),player1_idle_image->getHeight(),
        -100,-170,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow()
    );

    Image* player2_idle_image = idle_animations[player2_cursor][player2_idle_animation_image];
    rosalila()->graphics->draw2DImage
    (   player2_idle_image,
        player2_idle_image->getWidth(),player2_idle_image->getHeight(),
        780,80,
        1.0,
        0.0,
        true,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow()
    );

    rosalila()->graphics->drawText(menu_font, character_directories[player1_cursor], 85, 375, false, false);
    rosalila()->graphics->drawText(menu_font, character_directories[player2_cursor], 975, 627, false, false);

    rosalila()->update();
  }

  return 0;
}
