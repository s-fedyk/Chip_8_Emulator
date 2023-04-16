//
// Created by Stanislav Fedyk on 2023-04-15.
//

#ifndef CHIP_8_EMULATOR_INPUTADAPTER_H
#define CHIP_8_EMULATOR_INPUTADAPTER_H

#include <stdint.h>

class InputAdapter {
public:
    virtual uint8_t poll_for_input_no_blocking()=0;
    virtual uint8_t poll_for_input_blocking()=0;
};


#endif //CHIP_8_EMULATOR_INPUTADAPTER_H
