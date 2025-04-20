#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Hàm hiển thị menu chính
// Trả về 0 nếu chọn "Play", 1 nếu chọn "Exit"
int showMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* bg, Mix_Music* music);
