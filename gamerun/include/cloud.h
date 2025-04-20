#pragma once
#include "GameObject.h"

class Cloud :public GameObject {
private:
    int speed;

public:
    Cloud(SDL_Texture* tex, SDL_Renderer* rend, SDL_Rect r, int spd);
      
    void setRect(int x, int y, int w, int h);
    void move();
    void render();
};
