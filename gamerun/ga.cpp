#include "Ga.h"

const int GROUND_Y = 320;

Ga::Ga(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect)
    : GameObject(texture, renderer, rect), yVelocity(0.0f), isJumping(false), frameWidth(60), frameHeight(60), frameCount(4), currentFrame(0), lastFrameTime(SDL_GetTicks()), frameTime(1000 / 10) {
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
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= frameTime) {
        if (!isJumping) { // Chỉ chạy animation khi không nhảy
            currentFrame = (currentFrame + 1) % frameCount;
        }
        else {
            currentFrame = 0; // Khung hình cố định khi nhảy (hoặc thay bằng khung nhảy)
        }
        lastFrameTime = currentTime;
    }
}
void Ga::render() {
    SDL_Rect srcRect = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
    SDL_RenderCopy(renderer, texture, &srcRect, &rect);
}
SDL_Rect Ga::getRect() {
    return rect;
}
void Ga::setTexture(SDL_Texture* newTexture) {
    texture = newTexture;
}
void Ga::reset() {
    rect.y = GROUND_Y - 60;
    yVelocity = 0;
    isJumping = false;
}
