#include "include/ga.h"

const int GROUND_Y = 320;

Ga::Ga(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect)
    : GameObject(texture, renderer, rect), yVelocity(0.0f), isJumping(false) {
}

void Ga::jump() {
    if (!isJumping) {
        yVelocity = -12.0f;
        isJumping = true;
    }
}

void Ga::update() {
    if (isJumping) {
        rect.y += static_cast<int>(yVelocity);
        yVelocity += 0.6f;
        if (rect.y >= GROUND_Y - rect.h) {
            rect.y = GROUND_Y - rect.h;
            isJumping = false;
        }
    }
}
