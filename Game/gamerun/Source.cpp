    #define SDL_MAIN_HANDLED
    #include <SDL.h>
    #include <SDL_image.h>  // Thêm thư viện SDL_image để hỗ trợ PNG
    #include <SDL_ttf.h>
    #include <iostream>
    #include <cstdlib>
    #include <ctime>
    #include "include/GameObject.h"
    #include "include/Ga.h"
    #include <string>
    #include <vector>
    #include <cstdlib>
    using namespace std;

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 400;
    const int GROUND_Y = 320;
    const int NUM_BACKGROUNDS = 3;

    int bgIndex = 0;
    int nextBgIndex = 0;
    int fadeAlpha = 0;
    bool isFading = true;

    int randomInRange(int min, int max) { // ngẫu nhiên vị trí của mây
        return rand() % (max - min + 1) + min;
    } 
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
        SDL_Surface* surface = IMG_Load(path);  // Dùng IMG_Load thay vì SDL_LoadBMP để hỗ trợ PNG
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

    class Cloud {
    private:
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        SDL_Rect rect;
        int speed;

    public:
        Cloud(SDL_Texture* tex, SDL_Renderer* rend, SDL_Rect r, int spd)
            : texture(tex), renderer(rend), rect(r), speed(spd) {
        }

        void setRect(int x, int y, int w, int h) {
            rect.x = x;
            rect.y = y;
            rect.w = w;
            rect.h = h;
        }

        void move() {
            rect.x += speed;
            if (rect.x + rect.w < 0) { // Nếu mây đi hết màn hình, reset lại vị trí
                rect.x = SCREEN_WIDTH;  // Đặt lại vị trí mây ở bên phải màn hình
            }
        }

        void render() {
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
        }
    };
    int main(int argc, char* argv[]) {
        // Khởi tạo SDL và các thư viện cần thiết
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
        
        // Load textures
        SDL_Texture* backgrounds[NUM_BACKGROUNDS];
        backgrounds[0] = loadTexture(renderer, "assets/images/bg1.png");
        backgrounds[1] = loadTexture(renderer, "assets/images/bg2.png");
        backgrounds[2] = loadTexture(renderer, "assets/images/bg3.png");
        SDL_Texture* cloudTex = loadTexture(renderer, "assets/images/cloud.png");
      
        // Tạo các đối tượng SDL_Rect cho mặt trời, mặt trăng và hoàng hôn
      
        
        // Tạo đám mây
        vector<Cloud> clouds;
        for (int i = 0; i < 3; ++i) {
            int x = randomInRange(0, SCREEN_WIDTH); // Tọa độ x ngẫu nhiên từ 0 đến SCREEN_WIDTH
            int y = randomInRange(50, 200);         // Tọa độ y ngẫu nhiên từ 50 đến 200
            int speed = randomInRange(-2, -1);      // Tốc độ ngẫu nhiên, ví dụ từ -2 đến -1 để mây di chuyển từ phải sang trái
            clouds.push_back(Cloud(cloudTex, renderer, { x, y, 300, 150 }, speed));
        }
        // tạo đất 
        int groundX = 0;
        const int groundSpeed = 8;
    
        // Khởi tạo game objects
        SDL_Texture* groundTex = loadTexture(renderer, "assets/images/dat.png");
        SDL_Texture* gaTex = loadTexture(renderer, "assets/images/ga.png");
        SDL_Texture* cactusTex = loadTexture(renderer, "assets/images/fire.png");

        Ga ga(gaTex, renderer, { 50, GROUND_Y - 60, 60, 60 });
        GameObject cactus(cactusTex, renderer, { SCREEN_WIDTH, GROUND_Y - 40, 50, 60 });
        GameObject ground(groundTex, renderer, { 0, GROUND_Y, SCREEN_WIDTH, 80 });

        bool running = true;
        SDL_Event e;

        int score = 0;

        // Vòng lặp chính
        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                    ga.jump();
                }
            }
 
            // Cập nhật game
            SDL_RenderClear(renderer);

            // Vẽ các nền (background)
            if (bgIndex == 0) {
                SDL_RenderCopy(renderer, backgrounds[0], nullptr, nullptr);  // bg1
               
            }
            else if (bgIndex == 1) {
                SDL_RenderCopy(renderer, backgrounds[1], nullptr, nullptr);  // bg2
               
            }
            else if(bgIndex == 2){
                SDL_RenderCopy(renderer, backgrounds[2], nullptr, nullptr);  // bg3
               
            }

           
            
            //tạo đất 
            groundX -= groundSpeed;
            if (groundX <= -SCREEN_WIDTH) {
                groundX = 0;
            }
            // Cập nhật game
            ga.update();
            cactus.moveX(-8);

            // Tạo lại mảng mây nếu hết màn hình
            if (cactus.getRect().x + cactus.getRect().w < 0) {
                cactus.setX(SCREEN_WIDTH + rand() % 200);
                score++;

                int targetIndex = (score / 10) % NUM_BACKGROUNDS;
                // Chỉ bắt đầu fade nếu chưa fading và có nền mới cần chuyển
                if (!isFading && targetIndex != bgIndex) {
                    nextBgIndex = targetIndex;
                    isFading = true;
                    fadeAlpha = 0;  // Bắt đầu hiệu ứng mờ dần từ nền mới
                }
            }
            //di chuyển trăng trời
          

            SDL_Rect gaRect = ga.getRect();
            SDL_Rect cactusRect = cactus.getRect();
            if (SDL_HasIntersection(&gaRect, &cactusRect)) {
                std::cout << "Game Over! Score: " << score << std::endl;
                running = false;
            }

            // Xử lý fade nền
            const int FADE_SPEED = 5;
            SDL_RenderClear(renderer);
            if (!isFading) {
                SDL_RenderCopy(renderer, backgrounds[bgIndex], nullptr, nullptr);
            }
            else {
                // Vẽ nền cũ
                SDL_RenderCopy(renderer, backgrounds[bgIndex], nullptr, nullptr);

                // Vẽ nền mới với alpha tăng dần
                SDL_SetTextureBlendMode(backgrounds[nextBgIndex], SDL_BLENDMODE_BLEND);
                SDL_SetTextureAlphaMod(backgrounds[nextBgIndex], fadeAlpha);
                SDL_RenderCopy(renderer, backgrounds[nextBgIndex], nullptr, nullptr);
                SDL_SetTextureAlphaMod(backgrounds[nextBgIndex], 255);  // Reset alpha
                SDL_SetTextureBlendMode(backgrounds[nextBgIndex], SDL_BLENDMODE_NONE);  // Reset blend

                // Tăng alpha dần
                fadeAlpha += FADE_SPEED;
                if (fadeAlpha >= 255) {
                    fadeAlpha = 255;
                    bgIndex = nextBgIndex;
                    isFading = false;
                }
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
                cactus.render();

                SDL_RenderPresent(renderer);
                SDL_Delay(16);
            }

        // Cleanup và giải phóng tài nguyên
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
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
