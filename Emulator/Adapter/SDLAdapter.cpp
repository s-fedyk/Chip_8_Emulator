//
// Created by Stanislav Fedyk on 2023-04-14.
//

#include "SDLAdapter.h"
#include <iostream>

void SDLAdapter::draw(int x, int y) {
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
void SDLAdapter::clear() {
    std::cout << this->content->size() << std::endl;
    this->free_content();

    SDL_SetRenderDrawColor(this->renderer, 0,0,0,0);
    if (SDL_RenderClear(this->renderer) < 0) {
        std::cout << "render clera error\n";
    }
    SDL_RenderPresent(this->renderer);
}

SDLAdapter::SDLAdapter(SDL_Renderer *renderer) {
    this->content = new std::vector<SDL_Rect*>;
    this->content->clear();
    this->renderer = renderer;
}

SDLAdapter::~SDLAdapter() {
    free_content();
    delete(this->content);
}

void SDLAdapter::free_content() {
    for (auto box : *this->content) {
        delete(box);
    }
    this->content->clear();
}

