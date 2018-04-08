#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include <string>

#include "Rosalila/Rosalila.h"
#include "RosalilaFootsies/Footsies.h"
#include "RosalilaFootsies/Menus/TextInput.h"
#include "RosalilaFootsies/Menus/ContinueScreen.h"
#include "RosalilaFootsies/Menus/MainMenu.h"

#include <iostream>
using namespace std;

void renderFadeOutAnimation(vector<Image*> images, int size, int speed = 2)
{
  bool skipped = false;
  int aphaChannel = 255;
  int animation_frame = 0;

  while(aphaChannel >= 0 && skipped == false)
  {
    if(rosalila()->receiver->isJoyPressed(1,0)
        || rosalila()->receiver->isKeyPressed(SDLK_RETURN)
        || rosalila()->receiver->isJoyPressed(1,1))
    {
      skipped = true;
    }

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
  bool skipped = false;
  int aphaChannel = 0;
  int animation_frame = 0;

  while(aphaChannel <= 255 && skipped == false)
  {

    if(rosalila()->receiver->isJoyPressed(1,0) 
        || rosalila()->receiver->isKeyPressed(SDLK_RETURN)
        || rosalila()->receiver->isJoyPressed(1,1))
    {
      skipped = true;
    }

    if(animation_frame >= size)
    {
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
  modio_instance = new modio::Instance(MODIO_ENVIRONMENT_TEST, 70, "5bfdf943f8a8a109914ee20dbc64cf23");

  rosalila()->init();

  //Menu
  rosalila()->sound->addSound("start_screen",assets_directory + "menu/sounds/start_screen.ogg");
  rosalila()->sound->addSound("character_select_screen",assets_directory + "menu/sounds/character_select_screen.ogg");
  rosalila()->sound->addSound("confirm",assets_directory + "menu/sounds/confirm.ogg");
  rosalila()->sound->addSound("move_cursor",assets_directory + "menu/sounds/move_cursor.ogg");
  rosalila()->sound->addSound("start_pressed",assets_directory + "menu/sounds/start_pressed.ogg");

  //In game
  rosalila()->sound->addSound("countdown",assets_directory + "misc/sounds/countdown.ogg");
  rosalila()->sound->addSound("player1_wins",assets_directory + "misc/sounds/player1_wins.ogg");
  rosalila()->sound->addSound("player2_wins",assets_directory + "misc/sounds/player2_wins.ogg");



  rosalila()->sound->playMusic(assets_directory + "misc/intro_music.ogg", -1);

  vector<Image*> modio_images;
  modio_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/splash/modio.png"));
  renderFadeInAnimation(modio_images, (int)modio_images.size(), 3.5);
  renderFadeOutAnimation(modio_images, (int)modio_images.size(), 3);

  vector<Image*> rosalila_images;
  rosalila_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/splash/rosalila.png"));
  renderFadeInAnimation(rosalila_images, (int)rosalila_images.size(), 3.5);
  renderFadeOutAnimation(rosalila_images, (int)rosalila_images.size(), 3);

  vector<Image*> baka_images;
  baka_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/splash/baka_megane.png"));
  renderFadeInAnimation(baka_images, (int)baka_images.size(), 3.5);
  renderFadeOutAnimation(baka_images, (int)baka_images.size(), 3);

  rosalila()->sound->playSound("start_screen", -1, 0, 0, false);

  vector<Image*> intro_images;
  vector<int> intro_anim_velocities;

  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/1.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/2.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/3.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/4.png"));
  intro_images.push_back(rosalila()->graphics->getTexture(assets_directory + "intro/loading/blink.png"));

  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);
  intro_anim_velocities.push_back(8);

  renderContinueScreen(intro_images, intro_anim_velocities, (int)intro_images.size());

  mainMenu();

  return 0;
}
