//
// Created by edoardo biasio on 2021-03-05.
//

#include "selectable.hpp"
#include "../entity.hpp"
#include "../hex_map.hpp"
#include "hex.hpp"
#include "../game.hpp"

const std::string Selectable::id = "selectable";

Selectable::Selectable(Entity *owner, HexMap *map) : owner(owner), hex_map(map), is_selected(false) {
    assert(owner->has_component<Hex>());
    hex_component = owner->get_component<Hex>();
}

Selectable::Selectable(const Selectable& other, Entity* owner) : owner(owner), hex_map(other.hex_map), is_selected(other.is_selected) {
    assert(owner->has_component<Hex>());
    hex_component = owner->get_component<Hex>();
}

void Selectable::update(float dt) {
    Tile* tile = hex_map->get_tile_at_index(hex_component->get_position().x, hex_component->get_position().y);
    if (hex_map->get_selector()->selected_tile == tile) {
        is_selected = true;
        //std::cout << "Selected entity at position: " << hex_component->get_position().to_string() << std::endl;
    }
}

Component* Selectable::parse(std::vector<std::string> buffer, Entity *entity, Game* game) {
    Component* selectable = new Selectable(entity, game->get_hex_map());

    return selectable;
}

