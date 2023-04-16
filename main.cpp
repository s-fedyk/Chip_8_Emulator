#include <iostream>
#include "Emulator/Cpu.h"
#include "Emulator/Adapter/Graphics/SDLGraphicsAdapter.h"
#include "Emulator/Adapter/Input/SDLInputAdapter.h"
#include <SDL2/SDL.h>
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 320,
                                          0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);

    SDLGraphicsAdapter graphicsAdapter= SDLGraphicsAdapter(renderer);
    SDLInputAdapter inputAdapter = SDLInputAdapter();

    Cpu(&graphicsAdapter, &inputAdapter);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
