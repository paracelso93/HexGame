//
// Created by edoardo biasio on 2021-03-24.
//

#ifndef HEXGAME_MULTILINE_TEXT_HPP
#define HEXGAME_MULTILINE_TEXT_HPP

#include "text.hpp"
#include <vector>

class GUI_MultilineText {
private:
    std::vector<GUI_Text* > lines;

public:
    ~GUI_MultilineText();
    GUI_MultilineText(TTF_Font* font, std::string text, Color color, int x, int y, int line_offset);
    void render(SDL_Renderer* renderer);
};


#endif //HEXGAME_MULTILINE_TEXT_HPP
