//
// Created by Stanislav Fedyk on 2023-04-15.
//

#ifndef CHIP_8_EMULATOR_SDLINPUTADAPTER_H
#define CHIP_8_EMULATOR_SDLINPUTADAPTER_H


#include "InputAdapter.h"
#include <SDL_events.h>
#include <iostream>

class SDLInputAdapter : public InputAdapter {
    uint8_t poll_for_input_blocking() override;
    uint8_t poll_for_input_no_blocking() override;
};


#endif //CHIP_8_EMULATOR_SDLINPUTADAPTER_H
