//
// Created by edoardo biasio on 2021-03-02.
//

#include "camera.hpp"
#include <cmath>

Camera::Camera() : offset(0, 0) {

}

/*   0    --> dx
 *  0________________
 *   |               |
 *   |               | | dy
 *   |_______________| v
 *
 * */

void Camera::move(float dx, float dy) {
    direction.x = -dx * 100;
    direction.y = dy * 100;
}

void Camera::update(float dt) {
    offset.x += direction.x * dt;
    offset.y += direction.y * dt;
}

Vector2<int> Camera::screen_to_world(const Vector2<int>& position) const {
    int x = position.x - (int)offset.x;
    int y = position.y -  (int)offset.y;
    return Vector2<int>(x, y);
}