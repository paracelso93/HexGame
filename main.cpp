#include <iostream>
#include <SDL2/SDL.h>
#include <type_traits>
#include "parsers/unit_parser.hpp"

#include "SDLbase/texture_handler.hpp"
#include "hex_map.hpp"
#include "game.hpp"

int main() {
    Game game(1920, 1080, 26, 12);

    while (game.isOpen()) {
        game.tick();
    }

    return 0;
}
