//
// Created by edoardo biasio on 2021-03-04.
//

#ifndef HEXGAME_HEX_HPP
#define HEXGAME_HEX_HPP

#include "../component.hpp"
#include "../SDLbase/vectors.hpp"
#include "../SDLbase/helper.hpp"
#include "../hex_map.hpp"
#include "transform.hpp"

class Hex : public Component {
private:
    HexMap* currentMap;
    Vector2<int> hex_position;
    class Entity* owner;
    bool blocks;

public:
    Hex(const Hex& other, class Entity* owner);
    Hex(class Entity* owner, int x, int y, bool blocks, HexMap* map);
    void move(int x, int y, Transform* transform);
    void update(float dt) override {}
    Vector2<int> get_position() const { return hex_position; }
    static Component* parse(std::vector<std::string> buffer, class Entity* entity, class Game* game);

public:
    static const std::string id;
};

#endif //HEXGAME_HEX_HPP
