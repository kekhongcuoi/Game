#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color);
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path); 