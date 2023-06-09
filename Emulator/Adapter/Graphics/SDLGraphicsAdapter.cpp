//
// Created by Stanislav Fedyk on 2023-04-14.
//

#include "SDLGraphicsAdapter.h"

/** draw an entire sprite
 *
 * @param x
 * @param y
 * @param sprite mem address of the sprite
 * @param sprite_length the length of the sprite (in bytes)
 */
int SDLGraphicsAdapter::draw_sprite(uint8_t x,
                                     uint8_t y,
                                     uint8_t *sprite,
                                     uint8_t sprite_length)
{
    int collision_detected = 0;
    for (int height = 0; height < sprite_length; height++) {
        uint8_t current_sprite = sprite[height];
        for (int width = 0; width < 8; width++) {
            if ((bool)( (current_sprite >> (7-width) & 1))) {
                if (this->draw_buffer(x+width, y+height) > 0) {
                    collision_detected = 1;
                }
            }
        }
    }

    this->refresh_screen();
    SDL_RenderPresent(this->renderer);
    return collision_detected;
}

/** draw a single box unto the buffer (not drawn immediately)
 * @param x
 * @param y
 */
int SDLGraphicsAdapter::draw_buffer(uint8_t x, uint8_t y)
{

    //wrap around
    if (x >= 64){
        x = 0;
    }
    if (x < 0){
        x = 63;
    }
    if (y >= 32) {
        y = 0;
    }
    if (y < 0) {
        y = 31;
    }

    SDL_SetRenderDrawColor(this->renderer, 0,0,0,0);
    if (SDL_RenderClear(this->renderer)) {
        std::cout << "render clear error" << std::endl;
    }

    // pixels are "XORED" unto the screen.
    if (this->screen[y][x] == nullptr) {
        auto *new_box = new SDL_Rect();
        new_box->h = 10;
        new_box->w = 10;
        new_box->x = x*10;
        new_box->y = y*10;
        this->screen[y][x] = new_box;
        return 0;
    } else {
        delete(this->screen[y][x]);
        this->screen[y][x] = nullptr;
        return 1;
    }
}

/** Deallocates content buffer and clears screen
 *
 */
void SDLGraphicsAdapter::clear()
{
    this->free_content();

    SDL_SetRenderDrawColor(this->renderer, 0,0,0,0);
    if (SDL_RenderClear(this->renderer) < 0) {
        std::cout << "render clear error\n";
    }
    SDL_RenderPresent(this->renderer);
}

SDLGraphicsAdapter::SDLGraphicsAdapter(SDL_Renderer *renderer)
{
    memset(this->screen,0,32*64*sizeof(SDL_Rect*));
    this->renderer = renderer;
}

SDLGraphicsAdapter::~SDLGraphicsAdapter()
{
    free_content();
}

void SDLGraphicsAdapter::free_content()
{
    memset(this->screen, 0, 64*32*sizeof(SDL_Rect*));
}

/**
 * Goes through the screen buffer and draws
 */
void SDLGraphicsAdapter::refresh_screen() {
    SDL_SetRenderDrawColor(this->renderer, 255,255,255,0);
    for (auto & y : this->screen) {
        for (auto & x : y) {
            if (x != nullptr) {
                if (SDL_RenderFillRect(this->renderer, x) < 0) {
                    std::cout << "render failure\n";
                }
            }
        }
    }
}
