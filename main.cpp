#include <iostream>
#include "Emulator/Cpu.h"
#include "Emulator/Adapter/SDLAdapter.h"
#include <SDL2/SDL.h>
int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 320,
                                          0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);

    SDLAdapter adapter = SDLAdapter(renderer);
    Cpu cpu = Cpu(&adapter);

    while (true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
