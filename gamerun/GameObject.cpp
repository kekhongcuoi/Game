#include "GameObject.h"

GameObject::GameObject(SDL_Texture* tex, SDL_Renderer* rend, SDL_Rect r)
    : texture(tex), renderer(rend), rect(r) {
}

void GameObject::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect GameObject::getRect() {
    return rect;
}

void GameObject::setX(int x) {
    rect.x = x;
}

void GameObject::moveX(int dx) {
    rect.x += dx;
}
