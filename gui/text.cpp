//
// Created by edoardo biasio on 2021-03-02.
//

#include "text.hpp"

GUI_Text::GUI_Text(TTF_Font* font, std::string text, Color color, int x, int y) : text(text), color(color), position(x, y), font(font) {
    length = text.size();
}

void GUI_Text::render(SDL_Renderer* renderer) {
    SDL_Rect dst;
    SDL_Color c = {color.r, color.g, color.b, color.a};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), c);
    dst.x = position.x;
    dst.y = position.y;
    dst.w = surface->w;
    dst.h = surface->h;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

Vector2<int> GUI_Text::get_text_size() {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {0, 0, 0, 255});
    Vector2<int> size = Vector2<int>(surface->w, surface->h);
    SDL_FreeSurface(surface);
    return size;
}

void GUI_Text::set_position(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

void GUI_Text::set_text(const std::string &text) {
    this->text = text;
}