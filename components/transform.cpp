//
// Created by edoardo biasio on 2021-03-04.
//

#include "transform.hpp"
#include "../game.hpp"

const std::string Transform::id = "transform";

Transform::Transform(int x, int y, float x_scale, float y_scale, Color color) : position(x, y), scale(x_scale, y_scale), color(color) {
    Vector2<int> start_pos = calculate_engine_hex_position(HEX_SIDE_LENGTH);
    position.x += start_pos.x;
    position.y += start_pos.y;
}

Transform::Transform(const Transform &other, Entity* owner) : position(other.position), scale(other.scale), color(other.color) {

}

const Vector2<float> &Transform::get_position() const {
    return position;
}

void Transform::set_position(const Vector2<float> &position) {
    Transform::position = position;
}

const Vector2<float> &Transform::get_scale() const {
    return scale;
}

void Transform::set_scale(const Vector2<float> &scale) {
    Transform::scale = scale;
}

const Color &Transform::get_color() const {
    return color;
}

void Transform::set_color(const Color &color) {
    Transform::color = color;
}