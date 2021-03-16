//
// Created by edoardo biasio on 2021-03-04.
//

#include "renderable.hpp"
#include "../game.hpp"
#include "../entity.hpp"

const std::string Renderable::id = "renderable";

Renderable::Renderable(Entity* owner, std::string file_path, SDL_Renderer* renderer, int offset_x, int offset_y) : offset(offset_x, offset_y) {
    assert(owner->has_component<Transform>());
    this->renderer = renderer;
    this->file_path = file_path;
    texture = std::make_unique<Texture>(file_path, renderer);
    this->owner = owner;
    this->transform = owner->get_component<Transform>();
}

Renderable::Renderable(const Renderable &other, Entity* owner) : owner(owner), transform(new Transform(*other.transform, owner)), offset(other.offset) {
    assert(transform != nullptr);
    file_path = other.file_path;
    renderer = other.renderer;
    texture = std::make_unique<Texture>(other.file_path, other.renderer);
}

void Renderable::render(SDL_Renderer *renderer) {
    texture->render(renderer, Vector2<float>(transform->get_position().x + offset.x, transform->get_position().y + offset.y), transform->get_color(), transform->get_scale());
}

Component* Renderable::parse(std::vector<std::string> buffer, Entity *entity, Game* game) {
    std::string file_path = "";
    int off_x = 0, off_y = 0;
    while (!buffer.empty()) {
        std::string line = buffer[0];
        buffer.erase(buffer.begin());

        if (line.find("file_path:") != std::string::npos) {
            std::string val = line.substr(10);
            file_path = val;
        }

        if (line.find("offset_x:") != std::string::npos) {
            std::string val = line.substr(9);
            off_x = std::stoi(val);
        }

        if (line.find("offset_y:") != std::string::npos) {
            std::string val = line.substr(9);
            off_y = std::stoi(val);
        }
    }

    if (!entity->has_component<Transform>()) {
        entity->add_component<Transform>(new Transform(0, 0, 1, 1));
    }
    Component* renderable = new Renderable(entity, file_path, game->get_renderer(), off_x, off_y);

    return renderable;
}
