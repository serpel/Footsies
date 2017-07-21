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
    int y;
    int velocity_x;
    int velocity_y;

    Character* opponent;
    int player;
    bool game_started;
    bool button_up;
    bool is_bot;

    Character(int player, int x, bool is_bot);
    void draw();
    void logic();
    void cancel(string new_state);
    bool isFlipped();
    Move* getCurrentMove();
};

#endif
