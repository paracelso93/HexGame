//
// Created by edoardo biasio on 2021-03-19.
//

#include "unit_data_gui.hpp"
#include "../entity.hpp"
#include "../components/renderable.hpp"
#include "../components/unit_data.hpp"
#include "../gui/fonts.hpp"
#include "../gui/button.hpp"
#include "../game.hpp"

UnitDataGUI::UnitDataGUI(Game* game) : labels() {
    background = new GUI_Panel(500, 100, 500, 500, Color(214, 186, 24));
    background->set_exit_function([](void* data) {});
    background->get_exit_button()->set_colors(Color(100, 80, 10), Color(85, 74, 4));
    description_background = new GUI_Panel(510, 310, 480, 280, Color(200, 150, 20));
    top = new GUI_Draggable(500, 100 - 40, 460, 40, game);
    this->offset = Vector2<int>(0, 0);
    name = new GUI_Text(GUI_Fonts::get_instance()->get_font_with_size(30), "$name", BLACK, 520, 120);
    sprite = nullptr;
    labels.hp_label = nullptr;
    labels.armor_label = nullptr;
    labels.defence_label = nullptr;
    labels.damage_label = nullptr;
    labels.attack_label = nullptr;
    labels.description = nullptr;
    entity = nullptr;
    visible = false;
}

void UnitDataGUI::set_unit(Entity *entity) {
    assert(entity->has_component<Renderable>() && entity->has_component<UnitData>());
    visible = true;
    this->entity = entity;
    this->name->set_text(entity->get_type_id());
    sprite = entity->get_component<Renderable>()->get_texture();
    TTF_Font* f = GUI_Fonts::get_instance()->get_font_with_size(24);
    labels.hp_label = new GUI_Text(f, "hp: " + std::to_string(entity->get_component<UnitData>()->get_hp()) + "/" + std::to_string(entity->get_component<UnitData>()->get_total_hp()), BLACK, 520 + offset.x, 160 + offset.y);
    labels.armor_label = new GUI_Text(f, "armor: " + std::to_string(entity->get_component<UnitData>()->get_armor()), BLACK, 520 + offset.x, 190 + offset.y);
    labels.defence_label = new GUI_Text(f, "defence: " + std::to_string(entity->get_component<UnitData>()->get_defence_skill()), BLACK, 520 + offset.x, 220 + offset.y);
    labels.damage_label = new GUI_Text(f, "damage: " + std::to_string(entity->get_component<UnitData>()->get_damage()), BLACK, 520 + offset.x, 250 + offset.y);
    labels.attack_label = new GUI_Text(f, "attack: " + std::to_string(entity->get_component<UnitData>()->get_attack_skill()), BLACK, 520 + offset.x, 280 + offset.y);
    if (!entity->get_component<UnitData>()->get_description().empty()) {
        labels.description = new GUI_MultilineText(GUI_Fonts::get_instance()->get_font_with_size(20), entity->get_component<UnitData>()->get_description(), BLACK, 520 + offset.x, 310 + offset.y, 21);
    } else {
        labels.description = nullptr;
    }
}

void UnitDataGUI::update(float dt, Game* game) {
    background->get_exit_button()->update(game, visible);
    top->update(dt);
    if (top->is_dragging()) {
        game->set_cursor(DRAGGING);
        this->offset = top->get_offset();
        this->background->set_position(500 + offset.x, 100 + offset.y);
        name->set_position(520 + offset.x, 120 + offset.y);
        labels.hp_label->set_position(520 + offset.x, 160 + offset.y);
        labels.armor_label->set_position(520 + offset.x, 190 + offset.y);
        labels.defence_label->set_position(520 + offset.x, 220 + offset.y);
        labels.damage_label->set_position(520 + offset.x, 250 + offset.y);
        labels.attack_label->set_position(520 + offset.x, 280 + offset.y);
        if (labels.description != nullptr)
            labels.description->set_position(520 + offset.x, 310 + offset.y);
        description_background->set_position(510 + offset.x, 310 + offset.y);
        background->get_exit_button()->set_position(500 + offset.x + 460, 60 + offset.y);
    } else {
        if (!game->get_hovering())
            game->set_cursor(POINTING);
    }

    if (background->get_exit_button()->data_changed()) {
        visible = false;
        auto data = background->get_exit_button()->get_data();
    }
}

void UnitDataGUI::render(SDL_Renderer *renderer) {
    assert(entity != nullptr);


    background->render(renderer);
    description_background->render(renderer);
    this->sprite->render(renderer, {800 + (float)offset.x, 120 + (float)offset.y}, WHITE, {2.f, 2.f});
    name->render(renderer);
    labels.hp_label->render(renderer);
    labels.armor_label->render(renderer);
    labels.defence_label->render(renderer);
    labels.damage_label->render(renderer);
    labels.attack_label->render(renderer);
    if (labels.description != nullptr)
        labels.description->render(renderer);
}


