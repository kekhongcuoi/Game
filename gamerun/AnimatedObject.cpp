#include "AnimatedObject.h"
#include <SDL.h>

AnimatedObject::AnimatedObject(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect,
    int frameW, int frameH, int frameCount, int frameTime)
    : GameObject(texture, renderer, rect),
    frameWidth(frameW), frameHeight(frameH), frameCount(frameCount),
    currentFrame(0), lastFrameTime(SDL_GetTicks()), frameTime(frameTime) {
}

void AnimatedObject::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;
        lastFrameTime = currentTime;
    }
}

void AnimatedObject::render() {
    SDL_Rect srcRect = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
    SDL_RenderCopy(renderer, texture, &srcRect, &rect);
}
void AnimatedObject::setRect(const SDL_Rect& newRect) {
    this->rect = newRect;
}
