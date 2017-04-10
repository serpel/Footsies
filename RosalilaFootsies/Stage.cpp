#include "Stage.h"

Stage::Stage()
{
    background = rosalila()->graphics->getTexture(assets_directory+"/stages/background.png");
}

void Stage::draw()
{
    rosalila()->graphics->draw2DImage
    (   background,
        background->getWidth(),background->getHeight(),
        0,0,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow());
}

void Stage::logic()
{
}
