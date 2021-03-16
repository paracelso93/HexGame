//
// Created by edoardo biasio on 2021-02-03.
//

#ifndef ROGUELIKE_SDL_COLOR_HPP
#define ROGUELIKE_SDL_COLOR_HPP


#include <cstdint>

struct Color {
    uint8_t r, g, b, a;
    Color() : r(0), g(0), b(0), a(255) {}
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
    Color(int r, int g, int b) : r(r), g(g), b(b), a(255) {}
    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
};

static const Color WHITE(255, 255, 255);
static const Color RED(255, 0, 0);
static const Color GREEN(0, 255, 0);
static const Color BLUE(0, 0, 255);
static const Color YELLOW(255, 255, 0);
static const Color LIGHT_BLUE(0, 255, 255);
static const Color PINK(255, 0, 255);
static const Color BLACK(0, 0, 0);

#endif //ROGUELIKE_SDL_COLOR_HPP
