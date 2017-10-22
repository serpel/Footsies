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
    int counter;
    int frame;
    int player1_wins;
    int player2_wins;
    bool game_over;
    int game_over_frames;

    Footsies(string character1_name, string character2_name);
    void gameLoop();
};

#endif
