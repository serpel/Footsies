#ifndef STAGE_H
#define STAGE_H

#include "../../Rosalila/Rosalila.h"
#include "Layer.h"

class Layer;

class Stage
{
public:
    string name;
    vector<Layer*> layers;

    Stage(string name);
    void draw();
    void logic();
};

#endif
