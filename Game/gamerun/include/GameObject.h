#pragma once
#include <SDL.h>

class GameObject {
public:
    // Constructor
    GameObject(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect);

    // Render object
    void render();

    // Getter and setter methods for the rectangle
    SDL_Rect getRect();
    void setX(int x);
    void moveX(int dx);

protected:
    SDL_Texture* texture;    // The texture to render
    SDL_Renderer* renderer;  // The renderer to use for rendering
    SDL_Rect rect;           // The rectangle defining position and size
};
