#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cmath> // Thêm để sử dụng sin
#include "include/GameObject.h"
#include "include/Ga.h"
#include "include/AnimatedObject.h"
#include "include/cloud.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
const int GROUND_Y = 320;
const int NUM_BACKGROUNDS = 3;

int bgIndex = 0;
int nextBgIndex = 0;
int fadeAlpha = 0;
bool isFading = true;
float speedrun = 1.0f;


int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cerr << "Error loading image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
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


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(0)));

    SDL_Window* window = SDL_CreateWindow("Ga Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    TTF_Font* font = TTF_OpenFont("assets/fonts/WinkyRough-Light.ttf", 24); // Đảm bảo có font trong thư mục assets
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* backgrounds[NUM_BACKGROUNDS];
    backgrounds[0] = loadTexture(renderer, "assets/images/bg1.png");
    backgrounds[1] = loadTexture(renderer, "assets/images/bg2.png");
    backgrounds[2] = loadTexture(renderer, "assets/images/bg3.png");
    SDL_Texture* cloudTex = loadTexture(renderer, "assets/images/cloud.png");

    vector<Cloud> clouds;
    for (int i = 0; i < 3; ++i) {
        int x = randomInRange(0, SCREEN_WIDTH);
        int y = randomInRange(50, 200);
        int speed = randomInRange(-2, -1);
        clouds.push_back(Cloud(cloudTex, renderer, { x, y, 400, 150 }, speed));
    }

    int groundX = 0;
    const int groundSpeed = 8;

    SDL_Texture* groundTex = loadTexture(renderer, "assets/images/dat.png");
    SDL_Texture* gaTex = loadTexture(renderer, "assets/images/gachay.png");
    SDL_Texture* cactusTex = loadTexture(renderer, "assets/images/fire.png");
 
    Ga ga(gaTex, renderer, { 50, GROUND_Y - 60, 60, 60 });
    AnimatedObject cactus(cactusTex, renderer, { SCREEN_WIDTH, GROUND_Y - 40, 60, 60 },
        60, 60, 3, 1000/10); // frameW, frameH, frameCount, frameTime

    GameObject ground(groundTex, renderer, { 0, GROUND_Y, SCREEN_WIDTH, 80 });

    bool running = true;
    SDL_Event e;
    int score = 0;
    SDL_Color textColor = { 0, 0, 0, 255 }; // màu đen
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                ga.jump();
            }
        }
        SDL_RenderClear(renderer);

        //// Vẽ nền
        if (!isFading) {
            SDL_RenderCopy(renderer, backgrounds[bgIndex], nullptr, nullptr);
        }
        else {
            SDL_RenderCopy(renderer, backgrounds[bgIndex], nullptr, nullptr);
            SDL_SetTextureBlendMode(backgrounds[nextBgIndex], SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(backgrounds[nextBgIndex], fadeAlpha);
            SDL_RenderCopy(renderer, backgrounds[nextBgIndex], nullptr, nullptr);
            SDL_SetTextureAlphaMod(backgrounds[nextBgIndex], 255);
            SDL_SetTextureBlendMode(backgrounds[nextBgIndex], SDL_BLENDMODE_NONE);
            fadeAlpha += 5;
            if (fadeAlpha >= 255) {
                fadeAlpha = 255;
                bgIndex = nextBgIndex;
                isFading = false;
            }
        }

        // Di chuyển đất
        groundX -= static_cast<int>(groundSpeed * speedrun);
        if (groundX <= -SCREEN_WIDTH) {
            groundX = 0;
        }

        // Cập nhật game
        ga.update();
        cactus.moveX(static_cast<int>(-8 * speedrun));
        if (cactus.getRect().x + cactus.getRect().w < 0) {
            cactus.setX(SCREEN_WIDTH + rand() % 200);
            score++;
            speedrun = 1.0f + (score / 100.0f);
            int targetIndex = (score / 10) % NUM_BACKGROUNDS;
            if (!isFading && targetIndex != bgIndex) {
                nextBgIndex = targetIndex;
                isFading = true;
                fadeAlpha = 0;
            }
        }
        SDL_Rect gaRect = ga.getRect();
        SDL_Rect cactusRect = cactus.getRect();
        if (SDL_HasIntersection(&gaRect, &cactusRect)) {
            std::cout << "Game Over! Score: " << score << std::endl;
            running = false;
        }

        for (Cloud& cloud : clouds) {
            cloud.move();
            cloud.render();
        }

        SDL_Rect groundRect1 = { groundX, GROUND_Y, SCREEN_WIDTH, 80 };
        SDL_Rect groundRect2 = { groundX + SCREEN_WIDTH, GROUND_Y, SCREEN_WIDTH, 80 };
        SDL_RenderCopy(renderer, groundTex, nullptr, &groundRect1);
        SDL_RenderCopy(renderer, groundTex, nullptr, &groundRect2);

        ga.render();
        cactus.update();
        cactus.render();

        std::string scoreText = "Score: " + std::to_string(score);
        SDL_Texture* scoreTexture = renderText(renderer, font, scoreText, textColor);

        int textW = 0, textH = 0;
        SDL_QueryTexture(scoreTexture, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = { 10, 10, textW, textH }; // vị trí hiển thị

        SDL_RenderCopy(renderer, scoreTexture, nullptr, &textRect);
        SDL_DestroyTexture(scoreTexture); // Hủy texture sau khi vẽ

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Giải phóng tài nguyên
    for (int i = 0; i < NUM_BACKGROUNDS; ++i) {
        SDL_DestroyTexture(backgrounds[i]);
    }
    SDL_DestroyTexture(cloudTex);
    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(gaTex);
    SDL_DestroyTexture(cactusTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}