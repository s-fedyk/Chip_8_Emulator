//
// Created by Stanislav Fedyk on 2023-04-14.
//

#ifndef CHIP_8_EMULATOR_SDLADAPTER_H
#define CHIP_8_EMULATOR_SDLADAPTER_H


#include <SDL_render.h>
#include "GraphicsAdapter.h"
#include <vector>

class SDLAdapter: public GraphicsAdapter {
public:
    SDLAdapter(SDL_Renderer *renderer);
    ~SDLAdapter();
    void draw_sprite(uint8_t x, uint8_t y, uint8_t *sprite, uint8_t sprite_length) override;
    void draw(uint8_t x, uint8_t y);
    void clear() override;
    void free_content();

private:
    SDL_Renderer *renderer;
    std::vector<SDL_Rect*> *content;
};

#endif //CHIP_8_EMULATOR_SDLADAPTER_H
