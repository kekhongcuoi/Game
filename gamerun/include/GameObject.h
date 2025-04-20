
#pragma once
#include <SDL.h>

class GameObject {
public:
    GameObject(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect);
    void render();
    SDL_Rect getRect();
    void setX(int x);
    void moveX(int dx);

protected:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect rect;
};
