//#include "Fire.h"
//#include "TextureLoader.h" // n?u b?n c� class h? tr? load ?nh
//#include <SDL.h>
//
//Fire::Fire()
//    : AnimatedObject(nullptr, nullptr, { 800, 300, 50, 50 }, 50, 50, 2, 200) {
//    // m?c ??nh: ch?a c� texture v� renderer, 2 frame, m?i frame 200ms
//}
//
//void Fire::init() {
//    // Gi? s? b?n c� class TextureLoader ?? load ?nh
//    SDL_Texture* fireTexture = TextureLoader::loadTexture("assets/fire.png", renderer);
//    setTexture(fireTexture); // gi? s? b?n c� h�m setTexture() trong GameObject
//    rect.x = 800; // V? tr� b?t ??u b�n ph?i m�n h�nh
//    rect.y = 300;
//}
//
//void Fire::reset() {
//    rect.x = 800; // Reset l?i v? tr� ban ??u
//    currentFrame = 0; // Reset animation n?u c?n
//    lastFrameTime = SDL_GetTicks();
//}
