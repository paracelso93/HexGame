//
// Created by edoardo biasio on 2021-03-02.
//

#include "panel.hpp"
#include "button.hpp"
#include "fonts.hpp"

GUI_Panel::GUI_Panel(int x, int y, int w, int h, Color color) : position(x, y), size(w, h), color(color) {

        exit_button = nullptr;
}

void GUI_Panel::render(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = size.x;
    rect.h = size.y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    if (exit_button != nullptr) {
        SDL_Rect upper_rect;
        upper_rect.x = position.x;
        upper_rect.y = position.y - 40;
        upper_rect.w = size.x;
        upper_rect.h = 40;
        SDL_SetRenderDrawColor(renderer, 110, 87, 12, 255);
        SDL_RenderFillRect(renderer, &upper_rect);

        exit_button->render(renderer);
    }
}