//
// Created by edoardo biasio on 2021-03-19.
//

#ifndef HEXGAME_UNIT_DATA_GUI_HPP
#define HEXGAME_UNIT_DATA_GUI_HPP

#include "../gui/panel.hpp"
#include "../gui/text.hpp"
#include "../gui/multiline_text.hpp"
#include "../gui/draggable.hpp"
#include "../SDLbase/texture_handler.hpp"

struct DataLabels {
    GUI_Text* hp_label;
    GUI_Text* armor_label;
    GUI_Text* defence_label;
    GUI_Text* damage_label;
    GUI_Text* attack_label;
    GUI_MultilineText* description;
};

class UnitDataGUI {
private:
    GUI_Panel* background;
    GUI_Panel* description_background;
    GUI_Text* name;
    DataLabels labels;
    Texture* sprite;
    class Entity* entity;
    bool visible;
    GUI_Draggable* top;
    Vector2<int> offset;

public:
    UnitDataGUI(class Game* game);
    void render(SDL_Renderer* renderer);
    void set_unit(class Entity* entity);
    void update(float dt, class Game* game);
    void set_visible(bool visible) { this->visible = visible; }
    bool get_visible() const { return visible; }
};


#endif //HEXGAME_UNIT_DATA_GUI_HPP
