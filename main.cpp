#include <iostream>
#include <SDL2/SDL.h>
#include <type_traits>
#include "parsers/unit_parser.hpp"

#include "SDLbase/texture_handler.hpp"
#include "hex_map.hpp"
#include "game.hpp"

/*int c = 0;

template <typename ... bazinga>
typename std::enable_if<sizeof...(bazinga) == 0>::type func(int &i) {
    c++;
    if (c > 5) {
        return;
    }


    func<bazinga...>(i);
}

template <typename T, typename ... bazinga>
void func(int &i) {
    c++;
    std::cout << c << std::endl;
    if (c > 5) {
        return;
    }


    func<bazinga...>(i);
}*/

int main() {
    Game game(1920, 1080, 26, 12);

    while (game.isOpen()) {
        game.tick();
    }


    //Entity* chungus = UnitParser::create_entity_from_unit<Hex, Movable, Renderable, Selectable>(UnitParser::get_unit_with_id("tank"));
    //entities.push_back(chungus);

    return 0;
}