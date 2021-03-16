//
// Created by edoardo biasio on 2021-03-03.
//

#ifndef HEXGAME_BUTTON_HPP
#define HEXGAME_BUTTON_HPP

#include <functional>

#include "panel.hpp"
#include "text.hpp"

typedef unsigned char mouse_t;

class GUI_Button {
public:
    GUI_Button(int x, int y, int width, int height, Color bg_color, Color fg_color, TTF_Font* font, const std::string& text, std::function<void(void*) > callback);
    void update(const Vector2<int>& mouse_position, mouse_t mouse);
    void set_colors(Color hover, Color click);
    void* get_data() { updated = false; return this->data; }
    bool data_changed() const { return updated; }
    void render(SDL_Renderer* renderer);
private:
    std::unique_ptr<GUI_Panel> panel;
    std::unique_ptr<GUI_Text> text;
    Color bg_color;
    Color hover_color;
    Color click_color;
    bool pressing;

private:
    bool updated;
    std::function<void(void*) > callback;
    void* data;
};


#endif //HEXGAME_BUTTON_HPP
