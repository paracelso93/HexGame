//
// Created by edoardo biasio on 2021-03-04.
//

#ifndef HEXGAME_RENDERABLE_HPP
#define HEXGAME_RENDERABLE_HPP

#include <memory>

#include "../component.hpp"
#include "../SDLbase/texture_handler.hpp"
#include "transform.hpp"

class Renderable : public Component {
private:
    std::unique_ptr<Texture> texture;
    Transform* transform;
    SDL_Renderer* renderer;
    std::string file_path;
    Vector2<int> offset;
    class Entity* owner;
public:
    Renderable(Entity* owner, std::string file_path, SDL_Renderer* renderer, int offset_x, int offset_y);
    Renderable(const Renderable& other, class Entity* owner);
    static const std::string id;
    void render(SDL_Renderer* renderer);
    void update(float dt) override {}
    Transform* get_transform() { return transform; }
    ~Renderable() { delete transform; }
    static Component* parse(std::vector<std::string> buffer, class Entity* entity, class Game* game);
};


#endif //HEXGAME_RENDERABLE_HPP
