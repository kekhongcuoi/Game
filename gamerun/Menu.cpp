#include "include/Menu.h"
#include "include/TextUtils.h" // <- Thêm dòng này
#include <vector>
#include <string>
#include <iostream>
  // Set max volume

int showMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* menuBg, Mix_Music* menuMusic) {
    bool menuRunning = true;
    SDL_Event e;
    int selectedOption = 0; // 1: Play, 2: Exit
    int currentSelection = 0; // 0 = Play, 1 = Exit, 2 = Music
    bool musicOn = true;

    const int NUM_OPTIONS = 3;

    SDL_Rect optionRects[NUM_OPTIONS] = {
        {100, 150, 0, 0}, // Play
        {100, 250, 0, 0}, // Exit
        {100, 350, 0, 0}  // Music
    };
    
    while (menuRunning) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                selectedOption = 2;
                menuRunning = false;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_DOWN) {
                    currentSelection = (currentSelection + 1) % NUM_OPTIONS;
                }
                if (e.key.keysym.sym == SDLK_UP) {
                    currentSelection = (currentSelection - 1 + NUM_OPTIONS) % NUM_OPTIONS;
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    if (currentSelection == 0) { // Play
                        selectedOption = 1;
                        menuRunning = false;
                    }
                    else if (currentSelection == 1) { // Exit
                        selectedOption = 2;
                        menuRunning = false;
                    }
                    else if (currentSelection == 2) { // Music
                        musicOn = !musicOn;
                        if (musicOn) Mix_ResumeMusic();
                        else Mix_Pause(-1);
                        
                    }
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;
                for (int i = 0; i < NUM_OPTIONS; ++i) {
                    SDL_Rect rect = optionRects[i];
                    rect.w = 200;
                    rect.h = 50;
                    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
                        if (i == 0) { selectedOption = 1; menuRunning = false; }
                        else if (i == 1) { selectedOption = 2; menuRunning = false; }
                        else if (i == 2) {
                            musicOn = !musicOn;
                            if (musicOn) Mix_ResumeMusic();
                            else Mix_PauseMusic();
                                 
                        }
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuBg, nullptr, nullptr);

        SDL_Color normalColor = { 255, 255, 255, 255 };
        SDL_Color highlightColor = { 255, 255, 0, 255 };

        std::string options[NUM_OPTIONS] = {
            "Play",
            "Exit",
            musicOn ? "Music: On" : "Music: Off"
        };

        for (int i = 0; i < NUM_OPTIONS; ++i) {
            SDL_Color color = (i == currentSelection) ? highlightColor : normalColor;
            SDL_Texture* textTex = renderText(renderer, font, options[i], color);
            SDL_QueryTexture(textTex, nullptr, nullptr, &optionRects[i].w, &optionRects[i].h);
            SDL_RenderCopy(renderer, textTex, nullptr, &optionRects[i]);
            SDL_DestroyTexture(textTex);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return selectedOption;
}

