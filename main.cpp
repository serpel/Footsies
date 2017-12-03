#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include <string>

#include "Rosalila/Rosalila.h"
#include "RosalilaFootsies/Footsies.h"

#include <iostream>
using namespace std;

void renderFadeOutAnimation(vector<Image*> images, int size, int speed = 2)
{
  int aphaChannel = 255;
  int animation_frame = 0;

  while(aphaChannel >= 0)
  {

    if(animation_frame >= size){
      animation_frame = 0;
    }

    rosalila()->graphics->draw2DImage
    (
      images[animation_frame],
      images[animation_frame]->getWidth(),
      images[animation_frame]->getHeight(),
      rosalila()->graphics->screen_width/2 - images[animation_frame]->getWidth()/2,
      rosalila()->graphics->screen_height/2 - images[animation_frame]->getHeight()/2,
      1.0,
      0.0,
      false,
      0,0,
      Color(255,255,255,aphaChannel),
      0,0,
      false,
      FlatShadow()
    );

    aphaChannel -= speed;

    animation_frame++;

    rosalila()->update();

    rosalila()->graphics->clearScreen(Color(0,0,0,255));
  }
}

void renderFadeInAnimation(vector<Image*> images, int size, int speed = 2)
{
  int aphaChannel = 0;
  int animation_frame = 0;

  while(aphaChannel <= 255)
  {

    if(animation_frame >= size){
      animation_frame = 0;
    }

    rosalila()->graphics->draw2DImage
    (
      images[animation_frame],
      images[animation_frame]->getWidth(),
      images[animation_frame]->getHeight(),
      rosalila()->graphics->screen_width/2 - images[animation_frame]->getWidth()/2,
      rosalila()->graphics->screen_height/2 - images[animation_frame]->getHeight()/2,
      1.0,
      0.0,
      false,
      0,0,
      Color(255,255,255,aphaChannel),
      0,0,
      false,
      FlatShadow()
    );

    aphaChannel += speed;

    animation_frame++;

    rosalila()->update();

    rosalila()->graphics->clearScreen(Color(0,0,0,255));
  }
}

int main(int argc, char *argv[])
{
  rosalila()->init();

  //Menu
  rosalila()->sound->addSound("start_screen",assets_directory + "menu/sounds/start_screen.ogg");
  rosalila()->sound->addSound("character_select_screen",assets_directory + "menu/sounds/character_select_screen.ogg");
  rosalila()->sound->addSound("confirm",assets_directory + "menu/sounds/confirm.ogg");
  rosalila()->sound->addSound("move_cursor",assets_directory + "menu/sounds/move_cursor.ogg");

  //In game
  rosalila()->sound->addSound("countdown",assets_directory + "misc/sounds/countdown.ogg");
  rosalila()->sound->addSound("player1_wins",assets_directory + "misc/sounds/player1_wins.ogg");
  rosalila()->sound->addSound("player2_wins",assets_directory + "misc/sounds/player2_wins.ogg");

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

  vector<Image*> ready_anim;
  int p1_ready_framecounter = 0;
  int p2_ready_framecounter = 0;
  int ready_timing = 4;

  int p1_ready_currentframe = 0;
  int p2_ready_currentframe = 0;

  vector<string> ready_frame_names = rosalila()->utility->getFileNames(assets_directory + "menu/ready");
  for(int i = 0; i < ready_frame_names.size(); i++){
    ready_anim.push_back(rosalila()->graphics->getTexture(assets_directory + "menu/ready/" + ready_frame_names[i]));
  }

  int player1_cursor = 0;
  int player2_cursor = portraits.size()-1;
  int player1_selection = -1;
  int player2_selection = -1;

  TTF_Font* menu_font = NULL;

  string font_path = assets_directory+"misc/font.ttf";
  menu_font = TTF_OpenFont( font_path.c_str(), 28 );

  rosalila()->sound->playMusic(assets_directory + "misc/intro_music.ogg", -1);

  vector<Image*> intro_images;
  vector<int> intro_anim_velocities;
  //int intro_animation_velocity = 4;
  int intro_animation_frame = 0;
  int intro_animation_image = 0;

  //intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/iddle.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/1.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/2.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/3.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/4.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/blink.png"));

  //intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);

  vector<Image*> modio_images;
  modio_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/splash/modio.png"));
  renderFadeInAnimation(modio_images, (int)modio_images.size(), 3.5);
  renderFadeOutAnimation(modio_images, (int)modio_images.size());

  vector<Image*> rosalila_images;
  rosalila_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/splash/rosalila.png"));
  renderFadeInAnimation(rosalila_images, (int)rosalila_images.size(), 3.5);
  renderFadeOutAnimation(rosalila_images, (int)rosalila_images.size());

  vector<Image*> baka_images;
  baka_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/splash/baka_megane.png"));
  renderFadeInAnimation(baka_images, (int)baka_images.size());
  renderFadeOutAnimation(baka_images, (int)baka_images.size());

  rosalila()->sound->playSound("character_select_screen", -1, 0, 0, false);

  while(true){

    rosalila()->graphics->draw2DImage
    (   intro_images[intro_animation_image],
        intro_images[intro_animation_image]->getWidth(),intro_images[intro_animation_image]->getHeight(),
        rosalila()->graphics->screen_width/2 - intro_images[intro_animation_image]->getWidth()/2,
        rosalila()->graphics->screen_height/2 - intro_images[intro_animation_image]->getHeight()/2,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow()
    );

  intro_animation_frame++;
  if(intro_animation_frame > intro_anim_velocities[intro_animation_image])
  {
    intro_animation_frame = 0;
    intro_animation_image++;
    if(intro_animation_image >= (int)intro_images.size()-1)
    {
        intro_animation_image = 0;
    }
  }

  if(rosalila()->receiver->isJoyPressed(1,0) || rosalila()->receiver->isKeyPressed('w') ||
     rosalila()->receiver->isKeyPressed('i') || rosalila()->receiver->isJoyPressed(1,1))
  {

    //blink animation
    rosalila()->graphics->draw2DImage
    (   intro_images[(int)intro_images.size()-1],
        intro_images[(int)intro_images.size()-1]->getWidth(),intro_images[(int)intro_images.size()-1]->getHeight(),
        rosalila()->graphics->screen_width/2 - intro_images[(int)intro_images.size()-1]->getWidth()/2,
        rosalila()->graphics->screen_height/2 - intro_images[(int)intro_images.size()-1]->getHeight()/2,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow()
    );

    rosalila()->update();
    break;
  }

  rosalila()->update();
}

  rosalila()->sound->playMusic(assets_directory + "menu/music.ogg", -1);

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

        rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
      }

      if((rosalila()->receiver->isKeyPressed('a') && player1_selection == -1)
        || (rosalila()->receiver->isJoyPressed(-4,0) && player1_selection == -1))
      {
        player1_cursor--;
        if(player1_cursor < 0)
          player1_cursor = portraits.size()-1;
        player1_idle_animation_frame = 0;
        player1_idle_animation_image = 0;

        rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
      }

      if((rosalila()->receiver->isKeyPressed('l') && player1_selection == -1)
        || (rosalila()->receiver->isJoyPressed(-6,1) && player2_selection == -1))
      {
        player2_cursor++;
        if(player2_cursor >= (int)portraits.size())
           player2_cursor = 0;
        player2_idle_animation_frame = 0;
        player2_idle_animation_image = 0;

        rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
      }

      if((rosalila()->receiver->isKeyPressed('j') && player1_selection == -1)
        || (rosalila()->receiver->isJoyPressed(-4,1) && player2_selection == -1))
      {
        player2_cursor--;
        if(player2_cursor < 0)
          player2_cursor = portraits.size()-1;
        player2_idle_animation_frame = 0;
        player2_idle_animation_image = 0;

        rosalila()->sound->playSound("move_cursor", -1, 0, 0, false);
      }


      if(rosalila()->receiver->isJoyPressed(1,0) || rosalila()->receiver->isKeyPressed('w'))
      {
        player1_selection = player1_cursor;

        rosalila()->sound->playSound("confirm", -1, 0, 0, false);
      }

      if(rosalila()->receiver->isKeyPressed('i') || rosalila()->receiver->isJoyPressed(1,1))
      {
        player2_selection = player2_cursor;

        rosalila()->sound->playSound("confirm", -1, 0, 0, false);
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
        else{
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

          if(p1_ready_currentframe < ready_anim.size()-1 ){
            p1_ready_framecounter++;
            if(p1_ready_framecounter > ready_timing){
              p1_ready_framecounter = 0;
              p1_ready_currentframe ++;
            }
          }

          rosalila()->graphics->draw2DImage(
            ready_anim[p1_ready_currentframe],
            ready_anim[p1_ready_currentframe]->getWidth(), ready_anim[p1_ready_currentframe]->getHeight(),
            44, 155,
            1.0, 0.0, false, 0, 0, Color(255, 255, 255, 255), 0, 0, false, FlatShadow()
          );
        }
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
        else{
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

          if(p2_ready_currentframe < ready_anim.size()-1 ){
            p2_ready_framecounter++;
            if(p2_ready_framecounter > ready_timing){
              p2_ready_framecounter = 0;
              p2_ready_currentframe ++;
            }
          }

          rosalila()->graphics->draw2DImage(
            ready_anim[p2_ready_currentframe],
            ready_anim[p2_ready_currentframe]->getWidth(), ready_anim[p2_ready_currentframe]->getHeight(),
            944, 410,
            1.0, 0.0, false, 0, 0, Color(255, 255, 255, 255), 0, 0, false, FlatShadow()
          );
        }
      }
    }

    if(p1_ready_currentframe == ready_anim.size()-1 && p2_ready_currentframe == ready_anim.size()-1)
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
