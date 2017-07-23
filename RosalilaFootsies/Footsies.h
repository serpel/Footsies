#ifndef FOOTSIES_H
#define FOOTSIES_H

#include "Character.h"
#include "Stage/Stage.h"
#include "Move.h"
#include "Frame.h"

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

    Footsies();
    void gameLoop();
};

#endif
