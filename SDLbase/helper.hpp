#pragma once

#include <iostream>
#include <cmath>

#define PI 3.14159265
#define SIN_PI_6 0.5
#define COS_PI_6 0.86602540378
#define TAN_PI_6 0.57735026919

#define LOG(x, str) if (!x) { \
	std::cout << "Error, " << str << " failed." << std::endl; \
	return false; \
	}

#define MAX(a, b) return (a > b) ? a : b

inline static int distance(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    MAX(abs(dx), abs(dy));
}

inline static float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

inline static float calculate_hex_h(float side) {
    return static_cast<int>(SIN_PI_6 * side);
}

inline static float calculate_hex_r(float side) {
    return static_cast<int>(COS_PI_6 * side);
}

inline static float calculate_hex_b(float side, float h) {
    return side + 2 * h;
}

inline static float calculate_hex_a(float r) {
    return r * 2;
}

/*    ______--- = h
 *   /      \  |      |
 *  /        \ | = r  |
 * /          \|      |
 * \          /       | = a
 *  \        /        |
 *   \______/         |
 *    ------ = side
 * ------------- = b
 * */

inline static Vector2<int> calculate_engine_hex_position(float side) {
    return Vector2<int>(0 - 40 + (int)calculate_hex_h(side) / 2, 0 - 45 + (int)calculate_hex_r(side) / 2);
}