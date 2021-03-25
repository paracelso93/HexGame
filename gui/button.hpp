//
// Created by edoardo biasio on 2021-03-03.
//

#ifndef HEXGAME_BUTTON_HPP
#define HEXGAME_BUTTON_HPP

#include <functional>

#include "text.hpp"

typedef unsigned char mouse_t;

class GUI_Button {
public:
    GUI_Button(int x, int y, int width, int height, Color bg_color, Color fg_color, TTF_Font* font, const std::string& text);

    template <typename T>
    void set_function(std::function<void(void*)> callback) {
        this->callback = callback;
        this->data = new T();
    }

    void update(class Game* game, bool visible);
    void set_colors(Color hover, Color click);
    void* get_data() { updated = false; return this->data; }
    bool data_changed() const { return updated; }
    void render(SDL_Renderer* renderer);
    void set_position(int x, int y);
private:
    std::unique_ptr<class GUI_Panel> panel;
    std::unique_ptr<GUI_Text> text;
    Vector2<int> size;
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
