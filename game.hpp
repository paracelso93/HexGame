//
// Created by edoardo biasio on 2021-03-01.
//

#ifndef HEXGAME_GAME_HPP
#define HEXGAME_GAME_HPP

#include "hex_map.hpp"
#include "SDLbase/texture_handler.hpp"
#include "camera.hpp"
#include "gui/panel.hpp"
#include "gui/text.hpp"
#include "gui/fonts.hpp"
#include "gui/button.hpp"
#include "entity.hpp"
#include "components/renderable.hpp"
#include "components/hex.hpp"
#include "components/selectable.hpp"
#include "components/movable.hpp"
#include "SDLbase/a_star.hpp"
#include "components/unit_data.hpp"
#include "components/attacker.hpp"
#include "game_gui/unit_data_gui.hpp"
#include "gui/multiline_text.hpp"

#include <memory>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


typedef unsigned char mouse_t;
#define LEFT_BUTTON_DOWN 0x01 << 0
#define RIGHT_BUTTON_DOWN 0x01 << 1
#define MIDDLE_BUTTON_DOWN 0x01 << 2
#define LEFT_BUTTON_UP 0x01 << 3
#define RIGHT_BUTTON_UP 0x01 << 4
#define MIDDLE_BUTTON_UP 0x01 << 5

struct Info {
    GUI_Panel* bg_panel;
    GUI_Text* position_info;
    GUI_Text* entity_info;
    GUI_Text* entity_type_info;
};

class Game {
private:
    std::unique_ptr<HexMap> mMap;
    std::unique_ptr<Camera> mCamera;

    void update();
    void render();
    void handle_input();
    void init_sdl(int window_width, int window_height);

public:
    Game(int window_width, int window_height, int map_width, int map_height);
    void clean();
    void tick();
    bool isOpen() { return !mDone; }
    ~Game();
    const Vector2<int> get_map_size() const { return mMap->get_size(); }
    HexMap* get_hex_map() const { return mMap.get(); }
    SDL_Renderer* get_renderer() { return mRenderer; }
    Entity* get_entity_at_position(int x, int y);
    const Vector2<int>& get_mouse_position() { return mMousePosition; }
    const mouse_t get_mouse_state() { return mMouse; }

private:
    mouse_t mMouse;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mDone;
    Vector2<int> mMousePosition;
    float mDeltaTime;
    Uint32 startTime;
    int mWindowWidth;
    int mWindowHeight;
    Vector2<int> old_position;
    Texture* mCursorTexture;
    Texture* mPointerTexture;
    UnitDataGUI* unitDataGui;
    bool pointing;

    std::vector<Entity* > mEntities;
    Info* info;
};


#endif //HEXGAME_GAME_HPP
