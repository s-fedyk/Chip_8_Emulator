//
// Created by Stanislav Fedyk on 2023-04-14.
//

#ifndef CHIP_8_EMULATOR_GRAPHICSADAPTER_H
#define CHIP_8_EMULATOR_GRAPHICSADAPTER_H


#include <cstdint>

class GraphicsAdapter {
    public:
    virtual int draw_sprite(uint8_t x,uint8_t y, uint8_t* sprite, uint8_t sprite_length)=0;
    virtual void clear()=0;
};


#endif //CHIP_8_EMULATOR_GRAPHICSADAPTER_H
