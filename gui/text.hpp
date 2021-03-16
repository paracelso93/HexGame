//
// Created by edoardo biasio on 2021-03-02.
//

#ifndef HEXGAME_TEXT_HPP
#define HEXGAME_TEXT_HPP

#include "../SDLbase/color.hpp"
#include "../SDLbase/vectors.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class GUI_Text {
private:
    std::string text;
    Color color;
    Vector2<int> position;
    TTF_Font* font;
    int length;

public:
    GUI_Text(TTF_Font* font, std::string text, Color color, int x, int y);
    void render(SDL_Renderer* renderer);
    Vector2<int> get_text_size();
    void set_position(int x, int y);
    void set_text(const std::string& text);
};


#endif //HEXGAME_TEXT_HPP
