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
    std::string character1_name;
    std::string character2_name;
    Stage *stage;
    int frame;

    //hiteffect
    vector<Image*> hit_images;
    int hit_animation_velocity;
    int player1_hit_animation_framecounter;
    int player2_hit_animation_framecounter;
    int player1_hit_current_image;
    int player2_hit_current_image;
    bool player1_hit_active;
    bool player2_hit_active;
    int player1_hit_posx;
    int player2_hit_posx;
    int player1_hit_posy;
    int player2_hit_posy;

    //counter
    vector<Image*> counter_images;
    vector<int> counter_anim_velocities;
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
    vector<int> win_anim_velocities;
    int wins_animation_velocity;
    int wins_animation_frame;
    int wins_animation_image;

    Image* scoreboard_player1;
    Image* scoreboard_player2;

    TTF_Font* character_name_font;

    Footsies(string character1_name, string character2_name, int total_rounds);
    void gameLoop();
    void drawScoreboards();
};

#endif
