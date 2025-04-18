#include "include/GameObject.h"
#include <iostream>

GameObject::GameObject(SDL_Texture* tex, SDL_Renderer* rend, SDL_Rect r)
    : texture(tex), renderer(rend), rect(r) {
    if (!texture) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    if (!renderer) {
        std::cerr << "Renderer is null!" << std::endl;
    }
}

void GameObject::render() {
    if (texture && renderer) {
        // Render the texture on the screen at the position specified by rect
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    else {
        std::cerr << "Cannot render GameObject, texture or renderer is invalid!" << std::endl;
    }
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
