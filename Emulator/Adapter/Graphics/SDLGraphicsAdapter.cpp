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
void SDLGraphicsAdapter::draw_sprite(uint8_t x,
                                     uint8_t y,
                                     uint8_t *sprite,
                                     uint8_t sprite_length)
{
    for (int height = 0; height < sprite_length; height++) {
        uint8_t current_sprite = sprite[height];
        std::cout << std::hex << (int)current_sprite << std::endl;
        for (int width = 0; width < 8; width++) {
            if ((bool)( (current_sprite >> (7-width) & 1))) {
                this->draw(x+width, y+height);
            }
        }
    }
}

/** draw a single box
 * @param x
 * @param y
 */
void SDLGraphicsAdapter::draw(uint8_t x, uint8_t y)
{
    std::cout << "drawing" << std::endl;
    if (x > 64 || y > 32 || x < 0 || y < 0) {
        std::cout << "Warning: out of bounds draw occured\n";
    }

    SDL_SetRenderDrawColor(this->renderer, 0,0,0,0);
    if (SDL_RenderClear(this->renderer)) {
        std::cout << "render clear error" << std::endl;
    }

    auto *new_box = new SDL_Rect();
    new_box->h = 10;
    new_box->w = 10;
    new_box->x = x*10;
    new_box->y = y*10;
    this->content->push_back(new_box);

    SDL_SetRenderDrawColor(this->renderer, 255,255,255,0);

    for (auto box: *this->content) {
        if (SDL_RenderFillRect(this->renderer, box) < 0) {
            std::cout << "render failure\n";
        }
    }

    SDL_RenderPresent(this->renderer);
}

/** Deallocates content buffer and clears screen
 *
 */
void SDLGraphicsAdapter::clear()
{
    std::cout << this->content->size() << std::endl;
    this->free_content();

    SDL_SetRenderDrawColor(this->renderer, 0,0,0,0);
    if (SDL_RenderClear(this->renderer) < 0) {
        std::cout << "render clera error\n";
    }
    SDL_RenderPresent(this->renderer);
}

SDLGraphicsAdapter::SDLGraphicsAdapter(SDL_Renderer *renderer)
{
    this->content = new std::vector<SDL_Rect*>;
    this->content->clear();
    this->renderer = renderer;
}

SDLGraphicsAdapter::~SDLGraphicsAdapter()
{
    free_content();
    delete(this->content);
}

void SDLGraphicsAdapter::free_content()
{
    for (auto box : *this->content) {
        delete(box);
    }
    this->content->clear();
}
