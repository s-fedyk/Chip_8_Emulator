//
// Created by Stanislav Fedyk on 2023-04-14.
//

#ifndef CHIP_8_EMULATOR_GRAPHICSADAPTER_H
#define CHIP_8_EMULATOR_GRAPHICSADAPTER_H


class GraphicsAdapter {
    public:
    virtual void draw(int x,int y)=0;
    virtual void clear()=0;
};


#endif //CHIP_8_EMULATOR_GRAPHICSADAPTER_H
