#ifndef FOOTSIES_H
#define FOOTSIES_H

#include "Character/Character.h"
#include "Character/Move.h"
#include "Character/Frame.h"
#include "Stage/Stage.h"

class Character;

class Footsies
{
public:
    int initial_separation;
    int stage_boundaries;
    Character *character1;
    Character *character2;
    Stage *stage;
    int frame;

    //counter
    vector<Image*> counter_images;
    int counter_animation_velocity;
    int counter_animation_frame;
    int counter_animation_image;
    bool game_started;

    int player1_wins;
    int player2_wins;
    int total_rounds;
    bool game_over;
    int game_over_frames;
    
    vector<Image*> player1_wins_images;
    vector<Image*> player2_wins_images;
    int wins_animation_velocity;
    int wins_animation_frame;
    int wins_animation_image;

    Footsies(string character1_name, string character2_name, int total_rounds);
    void gameLoop();
};

#endif
