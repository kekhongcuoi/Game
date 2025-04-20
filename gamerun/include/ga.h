
#pragma once
#ifndef GA_H
#define GA_H

#include "GameObject.h"

class Ga : public GameObject {
public:
    Ga(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect);
    void jump();
    void update();
    void render();
    SDL_Rect getRect();
    void setTexture(SDL_Texture* newTexture);
    void reset();

private:
    
    float yVelocity;
    bool isJumping;
    int frameWidth;   // Chiều rộng mỗi khung hình
    int frameHeight;  // Chiều cao mỗi khung hình
    int frameCount;   // Số khung hình trong spritesheet
    int currentFrame; // Khung hình hiện tại
    Uint32 lastFrameTime; // Thời gian khung hình cuối
    int frameTime;
};

#endif
