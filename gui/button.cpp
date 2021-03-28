//
// Created by edoardo biasio on 2021-03-03.
//

#include "button.hpp"
#include "../game.hpp"
#include "panel.hpp"


GUI_Button::GUI_Button(int x, int y, int width, int height, Color bg_color, Color fg_color, TTF_Font* font, const std::string& text) {
    this->panel = std::make_unique<GUI_Panel>(x, y, width, height, bg_color);
    this->text = std::make_unique<GUI_Text>(font, text, fg_color, x, y);
    Vector2<int> text_size = this->text->get_text_size();
    this->text->set_position(x + (width - text_size.x) / 2, y + (height - text_size.y) / 2);
    this->data = nullptr;
    this->size = Vector2<int>(width, height);
    this->updated = false;
    this->callback = std::move(callback);
    this->bg_color = bg_color;
    this->hover_color = bg_color;
    this->click_color = bg_color;
    callback = [] (void*) {};
    pressing = false;
}

void GUI_Button::set_colors(Color hover, Color click) {
    this->hover_color = hover;
    this->click_color = click;
}

void GUI_Button::update(Game* game, bool visible) {
    if (updated) {
        updated = false;
    }
    auto mouse_position = game->get_mouse_position();
    auto mouse = game->get_mouse_state();

    if (mouse_position.x >= panel->get_position().x && mouse_position.x <= panel->get_position().x + panel->get_size().x &&
        mouse_position.y >= panel->get_position().y && mouse_position.y <= panel->get_position().y + panel->get_size().y) {
        if (mouse & LEFT_BUTTON_UP) {
            callback(data);
            updated = true;
            pressing = false;
            game->clicked_button = true;
            return;
        }
        if (mouse & LEFT_BUTTON_DOWN) {
            panel->set_color(click_color);
            pressing = true;
            if (visible) {
                game->set_cursor(POINTING);
            }
            return;
        }
        if (!pressing) {
            panel->set_color(hover_color);
            if (visible) {
                game->set_cursor(HOVERING);
            }
        }
        return;
    } else {
        game->set_cursor(POINTING);
    }
    panel->set_color(bg_color);
    pressing = false;
}

void GUI_Button::render(SDL_Renderer *renderer) {
    this->panel->render(renderer);
    this->text->render(renderer);
}

void GUI_Button::set_position(int x, int y) {
    this->panel->set_position(x, y);
    Vector2<int> text_size = this->text->get_text_size();
    this->text->set_position(x + (size.x - text_size.x) / 2, y + (size.y - text_size.y) / 2);
}