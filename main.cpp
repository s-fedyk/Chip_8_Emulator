#include <iostream>
#include "Emulator/Cpu.h"
#include <SDL2/SDL.h>
int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);
    std::cout << "Hello, World!" << std::endl;
    Cpu cpu = Cpu();
    return 0;
}
