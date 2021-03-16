//
// Created by edoardo biasio on 2021-03-05.
//

#include "movable.hpp"
#include "../entity.hpp"
#include "../game.hpp"
#include "hex.hpp"
#include "../SDLbase/a_star.hpp"

const std::string Movable::id = "movable";

Movable::Movable(Entity* owner, int max_move) : max_move(max_move), owner(owner) {
    assert(owner->has_component<Hex>());
}

Movable::Movable(const Movable &other, Entity* owner) : max_move(other.max_move), owner(owner) {

}

bool Movable::can_move(int new_x, int new_y) {
    Hex* hex = owner->get_component<Hex>();
    Node start;
    start.x = hex->get_position().x;
    start.y = hex->get_position().y;

    Node target;
    target.x = new_x;
    target.y = new_y;
    auto nodes = AStar::a_star(start, target);
    //for (auto node : nodes) {
    //    map->get_tile_at_index(node.x, node.y)->set_new_tile_texture("assets/base.png", renderer);
    //}
    return (nodes.size() <= max_move);
}

void Movable::move(int new_x, int new_y) {
//    if (can_move(new_x, new_y)) {
        Hex* hex = owner->get_component<Hex>();
        assert(owner->has_component<Transform>());
        int dx = new_x - hex->get_position().x;
        int dy = new_y - hex->get_position().y;
        hex->move(dx, dy, owner->get_component<Transform>());
 //   }
}

Component* Movable::parse(std::vector<std::string> buffer, Entity *entity, Game *game) {
    int movement = 0;

    while (!buffer.empty()) {
        std::string line = buffer[0];
        buffer.erase(buffer.begin());

        if (line.find("movement:") != std::string::npos) {
            std::string val = line.substr(9);
            try {
                movement = std::stoi(val);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }

    Component* movable = new Movable(entity, movement);
    return movable;
}
