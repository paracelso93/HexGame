//
// Created by edoardo biasio on 2021-03-04.
//

#include "hex.hpp"
#include "../entity.hpp"
#include "../game.hpp"
#include <string>

const std::string Hex::id = "hex";

Hex::Hex(Entity* owner, int x, int y, bool blocks, HexMap* map) : hex_position(x, y), currentMap(map), owner(owner), blocks(blocks) {
    map->get_tile_at_index(x, y)->blocks = blocks;
}

Hex::Hex(const Hex &other, Entity* owner) : hex_position(other.hex_position.x, other.hex_position.y), currentMap(other.currentMap), owner(owner), blocks(other.blocks) {
    currentMap->get_tile_at_index(hex_position.x, hex_position.y)->blocks = blocks;
}

void Hex::move(int x, int y, Transform* transform) {
    if (currentMap->check_boundaries(hex_position.x + x, hex_position.y + y) && !currentMap->get_tile_at_index(hex_position.x + x, hex_position.y + y)->blocks) {
        int old_x = hex_position.x;
        hex_position.x += x;
        hex_position.y += y;

        if (blocks) {
            currentMap->get_tile_at_index(hex_position.x, hex_position.y)->blocks = true;
        }

        if (transform != nullptr) {
            Vector2<float> newPos;
            newPos.x = transform->get_position().x + x * (calculate_hex_h(HEX_SIDE_LENGTH) + HEX_SIDE_LENGTH);
            newPos.y = transform->get_position().y + y * calculate_hex_a(calculate_hex_r(HEX_SIDE_LENGTH));
            if (hex_position.x % 2 == 1 && old_x % 2 == 0) {
                newPos.y += calculate_hex_r(HEX_SIDE_LENGTH);
            }
            if (hex_position.x % 2 == 0 && old_x % 2 == 1) {
                newPos.y -= calculate_hex_r(HEX_SIDE_LENGTH);
            }
            transform->set_position(newPos);
        }
    }
}

Component* Hex::parse(std::vector<std::string> buffer, Entity *entity, Game* game) {
    bool b_blocks = false;
    while (!buffer.empty()) {
        std::string line = buffer[0];
        buffer.erase(buffer.begin());

        if (line.find("blocks:") != std::string::npos) {
            std::string val = line.substr(7, 1);
            b_blocks = (val == "1");
        }
    }

    Component* hex = new Hex(entity, 0, 0, b_blocks, game->get_hex_map());
    return hex;
}
