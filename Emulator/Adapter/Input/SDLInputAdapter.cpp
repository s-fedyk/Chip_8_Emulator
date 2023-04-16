//
// Created by Stanislav Fedyk on 2023-04-15.
//

#include "SDLInputAdapter.h"

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
    while (true) {
     SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    std::cout << "keypress occured" << event.key.keysym.sym << std::endl;
                    switch (event.key.keysym.sym) {
                        case SDLK_0:
                            return 0x00;
                        case SDLK_1:
                            std::cout << "returning 1\n";
                            return 0x01;
                        case SDLK_2:
                            return 0x02;
                        case SDLK_3:
                            return 0x03;
                        case SDLK_4:
                            return 0x04;
                        case SDLK_5:
                            return 0x05;
                        case SDLK_6:
                            return 0x06;
                        case SDLK_7:
                            return 0x07;
                        case SDLK_8:
                            return 0x08;
                        case SDLK_9:
                            return 0x09;
                        case SDLK_a:
                            return 0x0A;
                        case SDLK_b:
                            return 0x0B;
                        case SDLK_c:
                            return 0x0C;
                        case SDLK_d:
                            return 0x0D;
                        case SDLK_e:
                            return 0x0E;
                        case SDLK_f:
                            return 0x0F;
                    }
                case SDL_KEYUP:
                    std::cout << "keypress occured" << event.key.keysym.sym << std::endl;
                    switch (event.key.keysym.sym) {
                        case SDLK_0:
                            return 0x00;
                        case SDLK_1:
                            std::cout << "returning 1\n";
                            return 0x01;
                        case SDLK_2:
                            return 0x02;
                        case SDLK_3:
                            return 0x03;
                        case SDLK_4:
                            return 0x04;
                        case SDLK_5:
                            return 0x05;
                        case SDLK_6:
                            return 0x06;
                        case SDLK_7:
                            return 0x07;
                        case SDLK_8:
                            return 0x08;
                        case SDLK_9:
                            return 0x09;
                        case SDLK_a:
                            return 0x0A;
                        case SDLK_b:
                            return 0x0B;
                        case SDLK_c:
                            return 0x0C;
                        case SDLK_d:
                            return 0x0D;
                        case SDLK_e:
                            return 0x0E;
                        case SDLK_f:
                            return 0x0F;
                    }
            }
        }
    }
}
