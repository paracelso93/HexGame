//
// Created by edoardo biasio on 2021-03-05.
//

#ifndef HEXGAME_MOVABLE_HPP
#define HEXGAME_MOVABLE_HPP

#include "../component.hpp"

class Movable : public Component {
private:
    int max_move;
    class Entity* owner;
public:
    static const std::string id;
    Movable(const Movable& other, class Entity* owner);
    Movable(class Entity* owner, int max_move);
    bool can_move(int new_x, int new_y);
    void move(int new_x, int new_y);
    void update(float dt) override {}
    static Component* parse(std::vector<std::string> buffer, class Entity* entity, class Game* game);
};


#endif //HEXGAME_MOVABLE_HPP
