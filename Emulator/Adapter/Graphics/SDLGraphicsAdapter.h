//
// Created by Stanislav Fedyk on 2023-04-14.
//

#ifndef CHIP_8_EMULATOR_SDLGRAPHICSADAPTER_H
#define CHIP_8_EMULATOR_SDLGRAPHICSADAPTER_H

#include <SDL_render.h>
#include "GraphicsAdapter.h"
#include <iostream>
#include <vector>

class SDLGraphicsAdapter: public GraphicsAdapter {
public:
    SDLGraphicsAdapter(SDL_Renderer *renderer);
    ~SDLGraphicsAdapter();
    int draw_sprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_length) override;
    int draw_buffer(uint8_t x, uint8_t y);
    void refresh_screen();
    void clear() override;
    void free_content();

private:
    SDL_Renderer *renderer;
    SDL_Rect* screen[32][64];
};

#endif //CHIP_8_EMULATOR_SDLGRAPHICSADAPTER_H
