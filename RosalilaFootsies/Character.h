#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Rosalila/Rosalila.h"
#include "Move.h"

class Move;

class Character
{
public:
    map< string, Move* > moves;
    string current_state;
    int frame;
    int animation_frame;
    int x;
    Character* opponent;
    int player;
    bool game_started;
    bool button_up;

    Character(int player, int x);
    void draw();
    void logic();
    void cancel(string new_state);
    bool isFlipped();
    Move* getCurrentMove();
};

#endif
