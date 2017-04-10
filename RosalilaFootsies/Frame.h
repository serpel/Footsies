#ifndef FRAME_H
#define FRAME_H

#include "../Rosalila/Rosalila.h"

class Frame
{
public:

    Image* image;
    int frame;
    int duration;
    bool finished;
    vector<Hitbox*> hitboxes;
    vector<Hitbox*> hurtboxes;

    Frame(Image* image, vector<Hitbox*> hitboxes, vector<Hitbox*> hurtboxes, int duration);
    void draw(int x, bool fipped);
    void logic();
    void restart();
    bool isFinished();
};

#endif
