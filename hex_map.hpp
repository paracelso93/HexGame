//
// Created by edoardo biasio on 2021-03-01.
//

#ifndef SDLBASELIB_HEX_MAP_H
#define SDLBASELIB_HEX_MAP_H

#include "SDLbase/vectors.hpp"
#include "SDLbase/color.hpp"
#include "SDLbase/helper.hpp"
#include "SDLbase/texture_handler.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <ctime>
#include <cstdlib>

static const int HEX_SIDE_LENGTH = 50;

struct Tile {
    Vector2<int> position;
    Vector2<int> world_position;
    Texture* tile_texture;
    bool blocks;
    //Color color;

    void set_new_tile_texture(const std::string& file_path, SDL_Renderer* renderer) {
        delete tile_texture;
        tile_texture = new Texture(file_path, renderer);
    }

    Tile(int x, int y, const std::string& file_path, SDL_Renderer* renderer) : position(x, y), tile_texture(nullptr) { //, color(0, 255, 0) {
        set_new_tile_texture(file_path, renderer);

        float h = calculate_hex_h(HEX_SIDE_LENGTH);
        world_position.x = h + (HEX_SIDE_LENGTH + h) * x;

        float r = calculate_hex_r(HEX_SIDE_LENGTH);
        world_position.y = 2 * r * y;
        if (x % 2 == 1) {
            world_position.y += (int)r;
        }

        blocks = false;
    }
};

static inline void draw_hex(SDL_Renderer* renderer, Color color, int x, int y) {
    Vector2<int> pos0 = Vector2<int>(x + 1, y + 1);
    Vector2<int> pos1 = Vector2<int>(x + HEX_SIDE_LENGTH, y + 1);
    float h = calculate_hex_h(HEX_SIDE_LENGTH);
    float r = calculate_hex_r(HEX_SIDE_LENGTH);
    Vector2<int> pos2 = Vector2<int>(static_cast<int>(x + HEX_SIDE_LENGTH + h), static_cast<int>(y + r));
    Vector2<int> pos3 = Vector2<int>(x + HEX_SIDE_LENGTH, static_cast<int>(y + r * 2));
    Vector2<int> pos4 = Vector2<int>(x + 1, static_cast<int>(y + r * 2));
    Vector2<int> pos5 = Vector2<int>(static_cast<int>(x - h + 1), static_cast<int>(y + r));

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, pos0.x, pos0.y, pos1.x, pos1.y);
    SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
    SDL_RenderDrawLine(renderer, pos2.x, pos2.y, pos3.x, pos3.y);
    SDL_RenderDrawLine(renderer, pos3.x, pos3.y, pos4.x, pos4.y);
    SDL_RenderDrawLine(renderer, pos4.x, pos4.y, pos5.x, pos5.y);
    SDL_RenderDrawLine(renderer, pos5.x, pos5.y, pos0.x, pos0.y);
}

static inline void draw_textured_hex(SDL_Renderer* renderer, int world_x, int world_y, Texture& texture) {
    texture.render(renderer, Vector2<float>(world_x - calculate_hex_h(HEX_SIDE_LENGTH), world_y));
}

struct Selector {
    Texture texture;
    Vector2<int> position;
    Tile* selected_tile;

    Selector(const std::string& file_path, SDL_Renderer* renderer);
    void update(const Vector2<int>& mousePosition, class HexMap* map, Camera* camera);
    void render(SDL_Renderer* renderer);
};

/*  ___     ___
 * /0,0\___/2,0\
 * \___/1,0\___/
 * /0,1\___/2,1\
 * \___/1,1\___/
 *     \___/
 * */

typedef std::vector<std::vector<Tile*> > TileMap;

class HexMap {
private:
    TileMap tiles;
    const int width, height;
    std::unique_ptr<Selector> selector;

public:
    HexMap(int width, int height, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void set_tile_selected(bool selected, int x, int y, SDL_Renderer* renderer);
    bool check_boundaries(int x, int y) { return !(x >= width || y >= height || x < 0 || y < 0); }
    void clean();
    const Vector2<int> get_size() const { return Vector2<int>(width, height); }
    void update(float dt, const Vector2<int>& mousePosition, bool mouseDown, Camera* camera);
    Vector2<int> get_hex_at_position(int x, int y);
    Tile* get_tile_at_index(int x, int y);
    Selector* get_selector() const { return selector.get(); }

};


#endif //SDLBASELIB_HEX_MAP_H
