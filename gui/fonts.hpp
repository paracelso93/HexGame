//
// Created by edoardo biasio on 2021-03-03.
//

#ifndef HEXGAME_FONTS_HPP
#define HEXGAME_FONTS_HPP

#include <SDL2/SDL_ttf.h>

#include <unordered_map>
#include <string>

typedef uint8_t font_size_t;

class GUI_Fonts {
public:
    static GUI_Fonts* get_instance() {
        if (instance == nullptr) {
            instance = new GUI_Fonts("assets/fonts/arial.ttf");
        }

        return instance;
    }

    explicit GUI_Fonts(std::string ffile_path);
    TTF_Font* get_font_with_size(font_size_t size);

private:
    std::string file_path;
    static GUI_Fonts* instance;
    std::unordered_map<font_size_t, TTF_Font* > fonts;
};


#endif //HEXGAME_FONTS_HPP
