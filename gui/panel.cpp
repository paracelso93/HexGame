//
// Created by edoardo biasio on 2021-03-02.
//

#include "panel.hpp"

GUI_Panel::GUI_Panel(int x, int y, int w, int h, Color color) : position(x, y), size(w, h), color(color) {

}

void GUI_Panel::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = size.x;
    rect.h = size.y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}