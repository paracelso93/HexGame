//
// Created by edoardo biasio on 2021-03-02.
//

#ifndef HEXGAME_PANEL_HPP
#define HEXGAME_PANEL_HPP

#include <SDL2/SDL.h>
#include "../SDLbase/vectors.hpp"
#include "../SDLbase/color.hpp"
#include "fonts.hpp"
#include "button.hpp"

class GUI_Panel {
private:
    Vector2<int> position;
    Vector2<int> size;
    Color color;
    GUI_Button* exit_button;

public:
    GUI_Panel(int x, int y, int w, int h, Color color);

    template <typename T = int>
    void set_exit_function(std::function<void(void*)> callback) {
        exit_button = new GUI_Button(position.x + size.x - 40, position.y - 40, 40, 40, Color(110, 87, 12), BLACK, GUI_Fonts::get_instance()->get_font_with_size(40), "X");
        exit_button->set_function<T>(callback);
    }
    void render(SDL_Renderer* renderer);
    void set_position(int x, int y) { position = Vector2<int>(x, y); }
    Vector2<int> get_size() const { return size; }
    Vector2<int> get_position() const { return position; }
    void set_color(Color color) { this->color = color; }
    GUI_Button* get_exit_button() { return exit_button; }
};


#endif //HEXGAME_PANEL_HPP
