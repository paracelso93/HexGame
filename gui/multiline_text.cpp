//
// Created by edoardo biasio on 2021-03-24.
//

#include "multiline_text.hpp"
#include <iostream>
#include <string>

GUI_MultilineText::GUI_MultilineText(TTF_Font *font, std::string text, Color color, int x, int y, int line_offset) {
    int position = 0;
    std::string line;
    std::string obama = text;
    int num_lines = 0;
    l_offset = line_offset;
    int old_position = 0;
    while (position < obama.length()) {
        if (obama[position] == '$' && obama[position + 1] == '$') {
            line = obama.substr(old_position, position - old_position);
            old_position = position + 2;
            //std::cout << line << std::endl;
            lines.push_back(new GUI_Text(font, line, color, x, y + line_offset * num_lines));
            //obama.erase(0, position + 1);
            num_lines++;
        }
        position++;
    }

    line = obama.substr(old_position, obama.length() - old_position);
    lines.push_back(new GUI_Text(font, line, color, x, y + line_offset * num_lines));
}

void GUI_MultilineText::render(SDL_Renderer *renderer) {
    for (auto line : lines) {
        line->render(renderer);
    }
}

GUI_MultilineText::~GUI_MultilineText() {
    for (auto line : lines) {
        delete line;
    }

    lines.empty();
}