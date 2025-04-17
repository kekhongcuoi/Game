#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/GameObject.h"
#include "../include/Ga.h"
#include <string>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
const int GROUND_Y = 320;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = SDL_LoadBMP(path);
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int main(int argc, char* argv[])  {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    srand(static_cast<unsigned int>(time(0)));

    SDL_Window* window = SDL_CreateWindow("Ga Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* bg = loadTexture(renderer, "assets/images/bg.bmp");
    SDL_Texture* groundTex = loadTexture(renderer, "assets/images/dat.bmp");
    SDL_Texture* gaTex = loadTexture(renderer, "assets/images/ga.bmp");
    SDL_Texture* cactusTex = loadTexture(renderer, "assets/images/fire.bmp");

    /*TTF_Font* font = TTF_OpenFont("assets/font.ttf", 24);
    SDL_Color white = {255, 255, 255};*/

    Ga ga(gaTex, renderer, {50, GROUND_Y - 60, 60, 60});
    GameObject cactus(cactusTex, renderer, {SCREEN_WIDTH, GROUND_Y - 40, 50, 60});
    GameObject ground(groundTex, renderer, {0, GROUND_Y, SCREEN_WIDTH, 80});

    int score = 0;
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                ga.jump();
            }
        }

        ga.update();
        cactus.moveX(-8);
        if (cactus.getRect().x + cactus.getRect().w < 0) {
            cactus.setX(SCREEN_WIDTH + rand() % 200);
            score++;
        }
        SDL_Rect gaRect = ga.getRect();
        SDL_Rect cactusRect = cactus.getRect();
        if (SDL_HasIntersection(&gaRect, &cactusRect)) {
            std::cout << "Game Over! Score: " << score << std::endl;
            running = false;
        }
    
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, nullptr, nullptr);
        ground.render();
        ga.render();
        cactus.render();

        std::string scoreText = "Score: " + std::to_string(score);
        //SDL_Texture* scoreTex = renderText(renderer, font, scoreText, white);
        SDL_Rect scoreRect = {10, 10, 150, 30};
        //SDL_RenderCopy(renderer, scoreTex, nullptr, &scoreRect);
        //SDL_DestroyTexture(scoreTex);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(gaTex);
    SDL_DestroyTexture(cactusTex);
    //  TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}