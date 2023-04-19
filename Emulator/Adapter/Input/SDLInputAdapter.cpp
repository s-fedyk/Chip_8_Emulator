//
// Created by Stanislav Fedyk on 2023-04-15.
//

#include "SDLInputAdapter.h"
/**
 * poll events and change the keyboard status
 * @param keyboard
 * @return
 */
int SDLInputAdapter::poll_for_input_no_blocking(bool keyboard[])
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return -1;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_0:
                    keyboard[0x00] = !(keyboard[0x00]);
                    break;
                case SDLK_1:
                    keyboard[0x01] = !(keyboard[0x01]);
                    break;
                case SDLK_2:
                    keyboard[0x02] = !(keyboard[0x02]);
                    break;
                case SDLK_3:
                    keyboard[0x03] = !(keyboard[0x03]);
                    break;
                case SDLK_4:
                    keyboard[0x04] = !(keyboard[0x04]);
                    break;
                case SDLK_5:
                    keyboard[0x05] = !(keyboard[0x05]);
                    break;
                case SDLK_6:
                    keyboard[0x06] = !(keyboard[0x06]);
                    break;
                case SDLK_7:
                    keyboard[0x07] = !(keyboard[0x07]);
                    break;
                case SDLK_8:
                    keyboard[0x08] = !(keyboard[0x08]);
                    break;
                case SDLK_9:
                    keyboard[0x09] = !(keyboard[0x09]);
                    break;
                case SDLK_a:
                    keyboard[0x0A] = !(keyboard[0x0A]);
                    break;
                case SDLK_b:
                    keyboard[0x0B] = !(keyboard[0x0B]);
                    break;
                case SDLK_c:
                    keyboard[0x0C] = !(keyboard[0x0C]);
                    break;
                case SDLK_d:
                    keyboard[0x0D] = !(keyboard[0x0D]);
                    break;
                case SDLK_e:
                    keyboard[0x0E] = !(keyboard[0x03]);
                    break;
                case SDLK_f:
                    keyboard[0x0F] = !(keyboard[0x0F]);
                    break;
            }
            return 1;
        }
    }
    return 1;
}

uint8_t SDLInputAdapter::poll_for_input_blocking()
{
    while (true) {
     SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_0:
                            return 0x00;
                        case SDLK_1:
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
