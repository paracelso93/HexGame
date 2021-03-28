//
// Created by edoardo biasio on 2021-03-28.
//

#include "entity_controller_gui.hpp"
#include "../components/movable.hpp"
#include "../gui/fonts.hpp"
#include "../entity.hpp"
#include "../game.hpp"

EntityControllerGUI::EntityControllerGUI() : current_entity(nullptr), movable_button(nullptr), moving_entity(false) {

    this->movable_button = new GUI_Button(200, 900, 50, 50, WHITE, BLACK, GUI_Fonts::get_instance()->get_font_with_size(24), "->");
    this->movable_button->set_function<int>([] (void*) {});
    this->movable_button->set_colors({250, 250, 250}, {240, 240, 240});
}

void EntityControllerGUI::set_entity(Entity *entity) {
    this->current_entity = entity;

    if (entity == nullptr) {

        movable_visible = false;
        return;
    }

    if (entity->has_component<Movable>()) {
        moving_entity = false;
        movable_visible = true;
    }
}

void EntityControllerGUI::update(float dt, Game *game) {
    if (movable_visible) {
        movable_button->update(game, true);

        if (this->movable_button->data_changed())
            moving_entity = true;
    }

    if (moving_entity && movable_visible) {
        Tile* tile = game->get_tile_selected();
        if (tile->position.x != current_entity->get_component<Hex>()->get_position().x || tile->position.y != current_entity->get_component<Hex>()->get_position().y) {
            if (this->current_entity->get_component<Movable>()->can_move(tile->position.x, tile->position.y)) {
                this->current_entity->get_component<Movable>()->move(tile->position.x, tile->position.y);
                moving_entity = false;
            }
        }
    }
}

void EntityControllerGUI::render(SDL_Renderer *renderer) {
    if (movable_visible) {
        movable_button->render(renderer);
    }
}