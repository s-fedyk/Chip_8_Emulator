//
// Created by Stanislav Fedyk on 2023-04-15.
//


#include "SDLInputAdapter.h"
#include <iostream>

uint8_t SDLInputAdapter::poll_for_input_no_blocking()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            std::cout << "exiting" << std::endl;
            return 0xFF;
        }

    }
    return 1;
}

uint8_t SDLInputAdapter::poll_for_input_blocking()
{
    return 0;
}
