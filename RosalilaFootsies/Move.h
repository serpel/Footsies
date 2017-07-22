#ifndef MOVE_H
#define MOVE_H

#include "../Rosalila/Rosalila.h"
#include "Frame.h"
#include "Character.h"

class Character;
class Frame;

class Move
{
public:
    Character* character;
    vector<Frame*> frames;
    int tick;
    int current_frame;
    bool finished;
    vector<string> cancels;
    vector< vector<string> >inputs;

    Move(Character* character,Node* move_node);
    void draw(int x, int y, bool fipped);
    void logic();
    void restart();
    bool isFinished();
    bool canCancel(string move);
    bool inputIsInBuffer();
    Frame* getCurrentFrame();
};

#endif
