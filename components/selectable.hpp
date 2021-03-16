//
// Created by edoardo biasio on 2021-03-05.
//

#ifndef HEXGAME_SELECTABLE_HPP
#define HEXGAME_SELECTABLE_HPP

#include "../SDLbase/vectors.hpp"
#include "../component.hpp"

class Selectable : public Component {
private:
    bool is_selected;
    class Entity* owner;
    class HexMap* hex_map;
    class Hex* hex_component;
    class Game* game;

public:
    static const std::string id;
    Selectable(class Entity* owner, class HexMap* map);
    Selectable(const Selectable& other, class Entity* owner);
    void update(float dt) override;
    bool get_selected() const { return is_selected; }
    static Component* parse(std::vector<std::string> buffer, class Entity* entity, class Game* game);
};


#endif //HEXGAME_SELECTABLE_HPP
