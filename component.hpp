//
// Created by edoardo biasio on 2021-03-04.
//

#ifndef HEXGAME_COMPONENT_HPP
#define HEXGAME_COMPONENT_HPP

#include <string>

class Component {
public:
    virtual void update(float dt) = 0;
    virtual ~Component() = default;
};

#endif //HEXGAME_COMPONENT_HPP
