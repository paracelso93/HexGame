//
// Created by edoardo biasio on 2021-03-02.
//

#ifndef HEXGAME_PANEL_HPP
#define HEXGAME_PANEL_HPP

#include <SDL2/SDL.h>
#include "../SDLbase/vectors.hpp"
#include "../SDLbase/color.hpp"

class GUI_Panel {
private:
    Vector2<int> position;
    Vector2<int> size;
    Color color;

public:
    GUI_Panel(int x, int y, int w, int h, Color color);
    void render(SDL_Renderer* renderer);
    Vector2<int> get_size() const { return size; }
    Vector2<int> get_position() const { return position; }
    void set_color(Color color) { this->color = color; }
};


#endif //HEXGAME_PANEL_HPP
