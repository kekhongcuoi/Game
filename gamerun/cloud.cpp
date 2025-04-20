#include"include/cloud.h"

Cloud::Cloud(SDL_Texture* tex, SDL_Renderer* rend, SDL_Rect r, int spd)
    : GameObject(tex, rend, r), speed(spd) {}
void Cloud::setRect(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Cloud::move() {
    rect.x += speed;
    if (rect.x + rect.w < 0) {
        rect.x = 800;
    }
}
void Cloud::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

