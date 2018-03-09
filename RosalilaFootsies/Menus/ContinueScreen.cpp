#include "TextInput.h"

void renderContinueScreen(vector<Image*> images, vector<int> intro_anim_velocities, int size, int minAlpha=128, int maxAlpha=255, int speed = 1)
{
  bool skipped = false;

  int start_text_flashes = 6;
  int start_text_flashcounter = 0;

  bool start_pressed = false;

  int intro_animation_frame = 0;
  int intro_animation_image = 0;
  //int alpha = minAlpha;

  while(true){

        if(!start_pressed){
          rosalila()->graphics->draw2DImage
          (
            images[intro_animation_image],
            images[intro_animation_image]->getWidth(),
            images[intro_animation_image]->getHeight(),
            rosalila()->graphics->screen_width/2 - images[intro_animation_image]->getWidth()/2,
            rosalila()->graphics->screen_height/2 - images[intro_animation_image]->getHeight()/2,
            1.0, 0.0, false, 0, 0, Color(255,255,255,255), 0, 0, false, FlatShadow()
          );

          intro_animation_frame++;
          if(intro_animation_frame > intro_anim_velocities[intro_animation_image])
          {
            intro_animation_frame = 0;
            intro_animation_image++;
            if(intro_animation_image >= size-1)
            {
                intro_animation_image = 0;
            }
          }

          if(rosalila()->receiver->isJoyPressed(1,0) || rosalila()->receiver->isKeyPressed('w') ||
            rosalila()->receiver->isKeyPressed('i') || rosalila()->receiver->isJoyPressed(1,1))
          {
            rosalila()->sound->playSound("start_pressed", -1, 0, 0, false);
            start_pressed = true;
            intro_animation_image = size-1;
            intro_animation_frame = 0;
          }
        }else{

          rosalila()->graphics->draw2DImage
          (
            images[intro_animation_image],
            images[intro_animation_image]->getWidth(),
            images[intro_animation_image]->getHeight(),
            rosalila()->graphics->screen_width/2 - images[size-1]->getWidth()/2,
            rosalila()->graphics->screen_height/2 - images[size-1]->getHeight()/2,
            1.0, 0.0, false, 0, 0, Color(255,255,255,255), 0, 0, false, FlatShadow()
          );

          intro_animation_frame++;
          if(intro_animation_frame > 6)
          {
            intro_animation_frame = 0;
            intro_animation_image++;

            if(intro_animation_image == size)
            {
                intro_animation_image = size-2;
                start_text_flashcounter ++;
            }
          }

          if(start_text_flashcounter == start_text_flashes){
            start_text_flashcounter = 0;
            intro_animation_frame = 0;
            intro_animation_image = 0;
            skipped = true;

            rosalila()->update();
            break;
          }
        }

      //rosalila()->graphics->clearScreen(Color(0,0,0,0));

      rosalila()->update();
    }
}
