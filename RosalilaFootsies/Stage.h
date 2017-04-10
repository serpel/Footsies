#ifndef STAGE_H
#define STAGE_H

#include "../Rosalila/Rosalila.h"

class Stage
{
public:

    Image* background;

    Stage();
    void draw();
    void logic();
};

#endif
