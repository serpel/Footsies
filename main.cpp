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
    int initial_separation = 200;
    int stage_boundaries = 250;
    Character *character1 = new Character(0,rosalila()->graphics->screen_width/2-initial_separation);
    Character *character2 = new Character(1,rosalila()->graphics->screen_width/2+initial_separation);
    character1->opponent = character2;
    character2->opponent = character1;
    Stage *stage = new Stage();
    int counter = 3;
    int frame = 1;
    int player1_wins = 0;
    int player2_wins = 0;
    while(true)
    {
        character1->logic();
        character2->logic();
        stage->draw();
        character1->draw();
        character2->draw();
        if(counter>0)
            rosalila()->graphics->drawText(rosalila()->utility->toString(counter), 0, 0, true, true);
        else
        {
            character1->game_started = true;
            character2->game_started = true;
        }
        rosalila()->graphics->drawText(rosalila()->utility->toString(player1_wins), -300, 100, true, false);
        rosalila()->graphics->drawText(rosalila()->utility->toString(player2_wins), 300, 100, true, false);

        if(frame%30==0)
            counter--;

        rosalila()->graphics->drawRectangle(0,620,
                                              stage_boundaries,100,0,
                                              255,255,255,128,true);
        rosalila()->graphics->drawRectangle(rosalila()->graphics->screen_width-stage_boundaries,620,
                                              stage_boundaries,100,0,
                                              255,255,255,128,true);

        vector<Hitbox*> character1_hitboxes = character1->getCurrentMove()->getCurrentFrame()->hitboxes;
        vector<Hitbox*> character2_hitboxes = character2->getCurrentMove()->getCurrentFrame()->hitboxes;
        vector<Hitbox*> character1_hurtboxes = character1->getCurrentMove()->getCurrentFrame()->hurtboxes;
        vector<Hitbox*> character2_hurtboxes = character2->getCurrentMove()->getCurrentFrame()->hurtboxes;
        bool character1_hit = false;
        bool character2_hit = false;
        bool hurtbox_collision = false;
        for(int i=0;i< (int)character1_hitboxes.size();i++)
        {
            Hitbox character1_hitbox = character1_hitboxes[i]->getPlacedHitbox(character1->x,0);
            if(character1->isFlipped())
                character1_hitbox = character1_hitboxes[i]->getFlippedHitbox().getPlacedHitbox(character1->x,0);

            for(int j=0;j< (int)character2_hurtboxes.size();j++)
            {
                Hitbox character2_hurtbox = character2_hurtboxes[j]->getPlacedHitbox(character2->x,0);
                if(character2->isFlipped())
                    character2_hurtbox = character2_hurtboxes[j]->getFlippedHitbox().getPlacedHitbox(character2->x,0);

                if(character1_hitbox.collides(character2_hurtbox))
                {
                    character2_hit = true;
                }
            }
        }
        for(int i=0;i< (int)character2_hitboxes.size();i++)
        {
            Hitbox character2_hitbox = character2_hitboxes[i]->getPlacedHitbox(character2->x,0);
            if(character2->isFlipped())
                character2_hitbox = character2_hitboxes[i]->getFlippedHitbox().getPlacedHitbox(character2->x,0);

            for(int j=0;j< (int)character1_hurtboxes.size();j++)
            {
                Hitbox character1_hurtbox = character1_hurtboxes[j]->getPlacedHitbox(character1->x,0);
                if(character1->isFlipped())
                    character1_hurtbox = character1_hurtboxes[j]->getFlippedHitbox().getPlacedHitbox(character1->x,0);

                if(character2_hitbox.collides(character1_hurtbox))
                {
                    character1_hit = true;
                }
            }
        }
        for(int i=0;i< (int)character2_hurtboxes.size();i++)
        {
            Hitbox character2_hurtbox = character2_hurtboxes[i]->getFlippedHitbox().getPlacedHitbox(character2->x,0);

            for(int j=0;j< (int)character1_hurtboxes.size();j++)
            {
                Hitbox character1_hurtbox = character1_hurtboxes[j]->getFlippedHitbox().getPlacedHitbox(character1->x,0);

                if(character2_hurtbox.collides(character1_hurtbox))
                {
                    hurtbox_collision = true;
                }
            }
        }

        if(character1_hit)
            character1->cancel("on_hit");
        if(character2_hit)
            character2->cancel("on_hit");
        if(hurtbox_collision)
        {
            character1->x-=2;
            character2->x+=2;
        }

        if(character1->x<=stage_boundaries || character1->x>=rosalila()->graphics->screen_width - stage_boundaries)
        {
            character1->cancel("idle");
            character1->x = rosalila()->graphics->screen_width/2-initial_separation;
            character2->cancel("idle");
            character2->x = rosalila()->graphics->screen_width/2+initial_separation;
            counter = 3;
            frame = 1;
            character1->game_started = false;
            character2->game_started = false;
            player2_wins++;
        }
        if(character2->x<=stage_boundaries || character2->x>=rosalila()->graphics->screen_width - stage_boundaries)
        {
            character1->cancel("idle");
            character1->x = rosalila()->graphics->screen_width/2-initial_separation;
            character2->cancel("idle");
            character2->x = rosalila()->graphics->screen_width/2+initial_separation;
            counter = 3;
            frame = 1;
            character1->game_started = false;
            character2->game_started = false;
            player1_wins++;
        }
        if(rosalila()->receiver->isKeyPressed('r'))
        {
            character1->cancel("idle");
            character1->x = rosalila()->graphics->screen_width/2-initial_separation;
            character2->cancel("idle");
            character2->x = rosalila()->graphics->screen_width/2+initial_separation;
            counter = 3;
            frame = 1;
            character1->game_started = false;
            character2->game_started = false;
            player1_wins = 0;
            player2_wins = 0;
        }
        frame++;
        rosalila()->update();
    }
    return 0;
}
