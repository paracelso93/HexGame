//
// Created by edoardo biasio on 2021-03-28.
//

#ifndef HEXGAME_ENTITY_CONTROLLER_GUI_HPP
#define HEXGAME_ENTITY_CONTROLLER_GUI_HPP

#include "../gui/button.hpp"

class EntityControllerGUI{
private:
    class Entity* current_entity;
    GUI_Button* movable_button;
    bool moving_entity;
    bool movable_visible;

public:
    EntityControllerGUI();
    void set_entity(class Entity* entity);
    void update(float dt, class Game* game);
    void render(SDL_Renderer* renderer);
    bool get_moving() { return moving_entity; }
};


#endif //HEXGAME_ENTITY_CONTROLLER_GUI_HPP
