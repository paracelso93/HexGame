//
// Created by edoardo biasio on 2021-03-03.
//

#include "fonts.hpp"

GUI_Fonts* GUI_Fonts::instance = nullptr;
GUI_Fonts::GUI_Fonts(std::string ffile_path) {
    this->file_path = std::move(ffile_path);
}

TTF_Font* GUI_Fonts::get_font_with_size(font_size_t size) {
    std::unordered_map<font_size_t, TTF_Font* >::const_iterator it = fonts.find(size);
    if (it == fonts.end()) {
        TTF_Font* new_font = TTF_OpenFont(file_path.c_str(), size);
        fonts[size] = new_font;
        return new_font;
    }

    return it->second;
}