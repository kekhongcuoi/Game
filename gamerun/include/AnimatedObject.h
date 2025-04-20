#pragma once
#include "GameObject.h"

class AnimatedObject : public GameObject {
public:
    AnimatedObject(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect,
        int frameW, int frameH, int frameCount, int frameTime);
    void update();
    void render();

private:
    int frameWidth;
    int frameHeight;
    int frameCount;
    int currentFrame;
    Uint32 lastFrameTime;
    int frameTime;
};