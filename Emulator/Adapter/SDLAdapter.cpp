//
// Created by Stanislav Fedyk on 2023-04-14.
//

#include "SDLAdapter.h"
#include <iostream>

void SDLAdapter::draw(int x, int y) {
    SDL_RenderClear(this->renderer);
    SDL_Rect box;
    box.h = 10;
    box.w = 10;
    box.x = x;
    box.y = y;

    SDL_SetRenderDrawColor(this->renderer, 255,255,255,0);
    SDL_RenderFillRect(this->renderer, &box);
    SDL_RenderPresent(this->renderer);
}

void SDLAdapter::clear() {
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}

SDLAdapter::SDLAdapter(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

