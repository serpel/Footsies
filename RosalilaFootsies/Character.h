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
    list<string> input_buffer;

    double x;
    double y;
    double velocity_x;
    double velocity_y;
    double acceleration_x;
    double acceleration_y;

    Character* opponent;
    int player;
    bool game_started;
    bool is_bot;

    Character(int player, int x, bool is_bot);
    void draw();
    void updateBuffer();
    void logic();
    void cancel(string new_state);
    bool isFlipped();
    Move* getCurrentMove();
};

#endif
