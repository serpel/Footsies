#include "Frame.h"

Frame::Frame(Image* image, vector<Hitbox*> hitboxes, vector<Hitbox*> hurtboxes, int duration)
{
    this->image = image;
    this->hitboxes = hitboxes;
    this->hurtboxes = hurtboxes;
    this->duration = duration;
    this->restart();
}

void Frame::draw(int x, bool flipped)
{
    rosalila()->graphics->draw2DImage
    (   image,
        image->getWidth(),image->getHeight(),
        x-image->getWidth()/2,620-image->getHeight(),
        1.0,
        0.0,
        flipped,
        0,0,
        Color(255,255,255,255),
        0,0,
        false,
        FlatShadow());

    if(rosalila()->receiver->isKeyDown('h'))
    if(!flipped)
    {
        for(int i=0;i< (int)hitboxes.size();i++)
            rosalila()->graphics->drawRectangle(hitboxes[i]->x + x,620-hitboxes[i]->y,
                                              hitboxes[i]->width,hitboxes[i]->height,0,
                                              255,0,0,128,true);

        for(int i=0;i< (int)hurtboxes.size();i++)
          rosalila()->graphics->drawRectangle(hurtboxes[i]->x + x,620-hurtboxes[i]->y,
                                              hurtboxes[i]->width,hurtboxes[i]->height,0,
                                              0,0,255,128,true);
    }else
    {
        for(int i=0;i< (int)hitboxes.size();i++)
            rosalila()->graphics->drawRectangle(-hitboxes[i]->x - hitboxes[i]->width + x,620-hitboxes[i]->y,
                                              hitboxes[i]->width,hitboxes[i]->height,0,
                                              255,0,0,128,true);

        for(int i=0;i< (int)hurtboxes.size();i++)
          rosalila()->graphics->drawRectangle(-hurtboxes[i]->x - hurtboxes[i]->width + x,620-hurtboxes[i]->y,
                                              hurtboxes[i]->width,hurtboxes[i]->height,0,
                                              0,0,255,128,true);
    }
}

void Frame::logic()
{
    frame++;
    if(frame >= duration)
        finished = true;
}

void Frame::restart()
{
    frame = 0;
    finished = false;
}

bool Frame::isFinished()
{
    return finished;
}
