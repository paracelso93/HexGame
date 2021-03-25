//
// Created by edoardo biasio on 2021-03-25.
//

#include "draggable.hpp"
#include "../game.hpp"

GUI_Draggable::GUI_Draggable(int x, int y, int w, int h, Game* game) {
    this->start_position = Vector2<int>(x, y);
    this->offset = Vector2<int>(0, 0);
    this->size = Vector2<int>(w, h);
    this->game = game;
    old_start_position = Vector2<int>(0, 0);
    dragging = false;
}

void GUI_Draggable::update(float dt) {
    auto mouse_position = game->get_mouse_position();
    if (game->get_mouse_state() & LEFT_BUTTON_DOWN) {

        if (mouse_position.x > start_position.x + offset.x && mouse_position.x < start_position.x + offset.x + size.x &&
            mouse_position.y > start_position.y + offset.y && mouse_position.y < start_position.y + offset.y + size.y) {
            if (!dragging) {
                starting_offset.x = mouse_position.x - start_position.x;
                starting_offset.y = mouse_position.y - start_position.y;
            }
            dragging = true;

        } else {
            dragging = false;
        }
    }

    if (dragging) {
        this->offset.x = old_start_position.x + mouse_position.x - starting_offset.x - start_position.x;
        this->offset.y = old_start_position.y + mouse_position.y - starting_offset.y - start_position.y;
    }

    if (game->get_mouse_state() & LEFT_BUTTON_UP) {
        old_start_position = offset;
        dragging = false;
    }
}