#include "GameObject.h"

GameObject::GameObject(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect)
    : texture(texture), renderer(renderer), rect(rect) {
}

void GameObject::render() {
    
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_SetTextureAlphaMod(texture, 255); // Đặt lại alpha để không ảnh hưởng đối tượng khác
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



