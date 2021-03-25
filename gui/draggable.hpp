//
// Created by edoardo biasio on 2021-03-25.
//

#ifndef HEXGAME_DRAGGABLE_HPP
#define HEXGAME_DRAGGABLE_HPP

#include "../SDLbase/vectors.hpp"

class GUI_Draggable {
private:
    Vector2<int> start_position;
    Vector2<int> offset;
    Vector2<int> size;
    Vector2<int> starting_offset;
    Vector2<int> old_start_position;
    class Game* game;
    bool dragging;
public:
    GUI_Draggable(int x, int y, int w, int h, class Game* game);
    bool is_dragging() const { return dragging; }
    void update(float dt);
    const Vector2<int>& get_offset() { return offset; }
};


#endif //HEXGAME_DRAGGABLE_HPP
