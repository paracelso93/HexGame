//
// Created by edoardo biasio on 2021-03-02.
//

#ifndef HEXGAME_CAMERA_HPP
#define HEXGAME_CAMERA_HPP

#include "SDLbase/vectors.hpp"

class Camera {
private:
    Vector2<float> offset;
    Vector2<float> direction;

public:
    const Vector2<float>& get_offset() const { return offset; }
    Camera();
    void move(float dx, float dy);
    void update(float dt);
    Vector2<int> screen_to_world(const Vector2<int>& position) const;
};

#endif //HEXGAME_CAMERA_HPP
