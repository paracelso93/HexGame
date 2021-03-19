//
// Created by edoardo biasio on 2021-03-19.
//

#ifndef HEXGAME_UNIT_DATA_GUI_HPP
#define HEXGAME_UNIT_DATA_GUI_HPP

#include "../gui/panel.hpp"
#include "../gui/text.hpp"
#include "../SDLbase/texture_handler.hpp"

// TODO(edoardo): add a description component
struct DataLabels {
    GUI_Text* hp_label;
    GUI_Text* armor_label;
    GUI_Text* defence_label;
    GUI_Text* damage_label;
    GUI_Text* attack_label;
};

class UnitDataGUI {
private:
    GUI_Panel* background;
    GUI_Text* name;
    DataLabels labels;
    Texture* sprite;
    class Entity* entity;

public:
    UnitDataGUI();
    void render(SDL_Renderer* renderer);
    void set_unit(class Entity* entity);
};


#endif //HEXGAME_UNIT_DATA_GUI_HPP
