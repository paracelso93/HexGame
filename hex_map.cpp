//
// Created by edoardo biasio on 2021-03-01.
//

#include "hex_map.hpp"

Selector::Selector(const std::string& file_path, SDL_Renderer* renderer) : texture(file_path, renderer), selected_tile(nullptr) {
    this->position = Vector2<int>(0, 0);
}

void Selector::update(const Vector2<int>& mousePosition, HexMap* map, Camera* camera) {
    //Vector2<int> tile_position = map->get_hex_at_position(mousePosition.x - (int)camera->get_offset().x, mousePosition.y - (int)camera->get_offset().y);
    Vector2<int> new_position = camera->screen_to_world(mousePosition);
    Vector2<int> tile_position = map->get_hex_at_position(new_position.x, new_position.y);
    if (map->check_boundaries(tile_position.x, tile_position.y)) {
        position = tile_position;
        selected_tile = map->get_tile_at_index(tile_position.x, tile_position.y);
        //std::cout << tile_position.to_string() << std::endl;
    }
}

void Selector::render(SDL_Renderer *renderer) {
    if (selected_tile == nullptr)
        return;
    draw_textured_hex(renderer, selected_tile->world_position.x, selected_tile->world_position.y, texture);
}

HexMap::HexMap(int width, int height, SDL_Renderer* renderer) : width(width), height(height) {
    selector = std::make_unique<Selector>("assets/selected.png", renderer);
    tiles.reserve(height);
    for (int i = 0; i < height; i++) {
        std::vector<Tile* > row;
        row.reserve(width);
        for (int j = 0; j < width; j++) {
            int tile = rand() % 5;
            std::string tile_file = "assets/grass.png";
            switch(tile) {
                case 0: tile_file = "assets/grass.png"; break;
                case 1: tile_file = "assets/grass2.png"; break;
                case 2: tile_file = "assets/grass3.png"; break;
                case 3: tile_file = "assets/grass4.png"; break;
                case 4: tile_file = "assets/grass5.png"; break;

                default: break;
            }
            row.push_back(new Tile(j, i, tile_file, renderer));
        }
        tiles.push_back(row);
    }
}

void HexMap::render(SDL_Renderer* renderer) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            draw_textured_hex(renderer, tiles[i][j]->world_position.x, tiles[i][j]->world_position.y, *tiles[i][j]->tile_texture);
        }
    }
    selector->render(renderer);
}

void HexMap::update(float dt, const Vector2<int>& mousePosition, bool mouseDown, Camera* camera) {
    if (mouseDown)
        selector->update(mousePosition, this, camera);
}

void HexMap::clean() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete tiles[i][j];
        }
    }

    tiles.clear();
}

Vector2<int> HexMap::get_hex_at_position(int x, int y) {
    int r = (int)calculate_hex_r(HEX_SIDE_LENGTH);
    int h = (int)calculate_hex_h(HEX_SIDE_LENGTH);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Tile* currentTile = tiles[i][j];
            if (y >= currentTile->world_position.y &&
                y <= currentTile->world_position.y + r * 2) {

                if (x >= currentTile->world_position.x &&
                    x <= currentTile->world_position.x + HEX_SIDE_LENGTH) {
                    return Vector2<int>(j, i);
                }

                if (x >= currentTile->world_position.x + HEX_SIDE_LENGTH &&
                    x <= currentTile->world_position.x + HEX_SIDE_LENGTH + h) {
                    double offset = (x - currentTile->world_position.x - HEX_SIDE_LENGTH) / TAN_PI_6;
                    if (offset >= 0 && y >= offset + currentTile->world_position.y && y <= currentTile->world_position.y + 2 * r - offset) {
                        return Vector2<int>(j, i);
                    }
                }
                if (x >= currentTile->world_position.x - h &&
                 x <= currentTile->world_position.x) {
                    double offset = (currentTile->world_position.x - x) / TAN_PI_6;

                    if (offset >= 0 && y >= offset + currentTile->world_position.y && y <= currentTile->world_position.y + 2 * r - offset) {
                        return Vector2<int>(j, i);
                    }
                }
            }
        }
    }
    return Vector2<int>(-1, -1);
}

Tile* HexMap::get_tile_at_index(int x, int y) {
    if (check_boundaries(x, y)) {
        return tiles[y][x];
    }
    return nullptr;
}

void HexMap::set_tile_selected(bool selected, int x, int y, SDL_Renderer* renderer) {
    if (check_boundaries(x, y)) {
        if (selected)
            tiles[y][x]->set_new_tile_texture("assets/selected.png", renderer);
        else
            tiles[y][x]->set_new_tile_texture("assets/base.png", renderer);
    } else {
        std::cerr << "Please enter a valid coordinate, " << x << "," << y << " is not a valid coordinate" << std::endl;
    }
}
