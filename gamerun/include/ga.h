
#pragma once
#ifndef GA_H
#define GA_H

#include "GameObject.h"

class Ga : public GameObject {
public:
    Ga(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect);
    void jump();
    void update();

private:
    float yVelocity;
    bool isJumping;
};

#endif
