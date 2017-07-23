#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../Rosalila/Rosalila.h"
#include "../Footsies.h"
#include "Move.h"

class Footsies;
class Move;

class Character
{
public:
    Footsies* footsies;
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
    string name;

    Character(Footsies* footsies, int player, int x, string name);
    void draw();
    void updateBuffer();
    void logic();
    void cancel(string new_state);
    bool isFlipped();
    bool isInBounds();
    Move* getCurrentMove();
};

#endif
