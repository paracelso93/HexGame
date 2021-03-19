//
// Created by edoardo biasio on 2021-03-19.
//

#include "unit_data_gui.hpp"
#include "../entity.hpp"
#include "../components/renderable.hpp"
#include "../components/unit_data.hpp"
#include "../gui/fonts.hpp"

UnitDataGUI::UnitDataGUI() : labels() {
    background = new GUI_Panel(500, 100, 500, 500, Color(214, 186, 24));
    name = new GUI_Text(GUI_Fonts::get_instance()->get_font_with_size(30), "$name", BLACK, 520, 120);
    sprite = nullptr;
    labels.hp_label = nullptr;
    labels.armor_label = nullptr;
    labels.defence_label = nullptr;
    labels.damage_label = nullptr;
    labels.attack_label = nullptr;
    entity = nullptr;
}

void UnitDataGUI::set_unit(Entity *entity) {
    assert(entity->has_component<Renderable>() && entity->has_component<UnitData>());
    this->entity = entity;
    this->name->set_text(entity->get_type_id());
    sprite = entity->get_component<Renderable>()->get_texture();
    TTF_Font* f = GUI_Fonts::get_instance()->get_font_with_size(24);
    labels.hp_label = new GUI_Text(f, "hp: " + std::to_string(entity->get_component<UnitData>()->getHp()) + "/" + std::to_string(entity->get_component<UnitData>()->getTotalHp()), BLACK, 520, 160);
    labels.armor_label = new GUI_Text(f, "armor: " + std::to_string(entity->get_component<UnitData>()->getArmor()), BLACK, 520, 190);
    labels.defence_label = new GUI_Text(f, "defence: " + std::to_string(entity->get_component<UnitData>()->getDefenceSkill()), BLACK, 520, 220);
    labels.damage_label = new GUI_Text(f, "damage: " + std::to_string(entity->get_component<UnitData>()->getDamage()), BLACK, 520, 250);
    labels.attack_label = new GUI_Text(f, "attack: " + std::to_string(entity->get_component<UnitData>()->getAttackSkill()), BLACK, 520, 280);
}

void UnitDataGUI::render(SDL_Renderer *renderer) {
    assert(entity != nullptr);

    background->render(renderer);
    this->sprite->render(renderer, {800, 120}, WHITE, {2.f, 2.f});
    name->render(renderer);
    labels.hp_label->render(renderer);
    labels.armor_label->render(renderer);
    labels.defence_label->render(renderer);
    labels.damage_label->render(renderer);
    labels.attack_label->render(renderer);
}

