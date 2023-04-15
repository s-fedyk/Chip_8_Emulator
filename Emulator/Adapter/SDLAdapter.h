//
// Created by Stanislav Fedyk on 2023-04-14.
//

#ifndef CHIP_8_EMULATOR_SDLADAPTER_H
#define CHIP_8_EMULATOR_SDLADAPTER_H


#include <SDL_render.h>
#include "GraphicsAdapter.h"

class SDLAdapter: public GraphicsAdapter {
public:
    SDLAdapter(SDL_Renderer *renderer);
    void draw(int x, int y) override;
    void clear() override;

private:
    SDL_Renderer *renderer;
};

#endif //CHIP_8_EMULATOR_SDLADAPTER_H
