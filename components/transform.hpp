//
// Created by edoardo biasio on 2021-03-04.
//

#ifndef HEXGAME_TRANSFORM_HPP
#define HEXGAME_TRANSFORM_HPP


#include "../component.hpp"
#include "../SDLbase/vectors.hpp"
#include "../SDLbase/color.hpp"

class Transform : public Component {
private:
    Vector2<float> position;
    Vector2<float> scale;
    Color color;

public:
    void update(float dt) override {}
    Transform(int x, int y, float x_scale = 1.f, float y_scale = 1.f, Color color = WHITE);
    Transform(const Transform& other, class Entity* owner);
    const Vector2<float> &get_position() const;
    void set_position(const Vector2<float> &position);
    const Vector2<float> &get_scale() const;
    void set_scale(const Vector2<float> &scale);
    const Color &get_color() const;
    void set_color(const Color &color);

    static const std::string id;
};


#endif //HEXGAME_TRANSFORM_HPP
