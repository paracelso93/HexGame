cmake_minimum_required(VERSION 3.13)
project(hexGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(hexGame main.cpp SDLbase/color.cpp SDLbase/texture_handler.cpp hex_map.cpp game.cpp game.hpp camera.cpp camera.hpp gui/panel.cpp gui/panel.hpp gui/text.cpp gui/text.hpp gui/fonts.cpp gui/fonts.hpp gui/button.cpp gui/button.hpp entity.hpp component.hpp components/renderable.cpp components/renderable.hpp components/transform.cpp components/transform.hpp components/hex.cpp components/hex.hpp components/selectable.cpp components/selectable.hpp components/movable.cpp components/movable.hpp SDLbase/a_star.cpp SDLbase/a_star.hpp parsers/unit_parser.cpp parsers/unit_parser.hpp entity.cpp components/unit_data.cpp components/unit_data.hpp game_gui/unit_data_gui.cpp game_gui/unit_data_gui.hpp components/attacker.cpp SDLbase/random_handler.cpp SDLbase/random_handler.hpp gui/multiline_text.cpp gui/multiline_text.hpp gui/draggable.cpp gui/draggable.hpp game_gui/entity_controller_gui.cpp game_gui/entity_controller_gui.hpp)
target_link_libraries(hexGame SDL2 SDL2_ttf SDL2_image)