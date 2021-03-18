//
// Created by edoardo biasio on 2021-03-04.
//

#ifndef HEXGAME_ENTITY_HPP
#define HEXGAME_ENTITY_HPP

#include <unordered_map>
#include <string>

#include "component.hpp"

typedef unsigned int entity_id;

class Entity {
private:
    std::string type_id;
    static entity_id current_id;
    entity_id id;
    std::unordered_map<std::string, Component* > components;
public:
    Entity(const std::string& type_id, bool is_model = false) {
        this->type_id = type_id;
        if (!is_model) {
            this->id = current_id;
            current_id++;
        } else {
            this->id = -1;
        }
    }

    void set_type_id(const std::string& type_id) { this->type_id = type_id; }
    std::string get_type_id() const { return this->type_id; }

    entity_id get_id() const { return this->id; }

    void update(float dt) {
        for (const auto& component : components) {
            component.second->update(dt);
        }
    }

    template <typename T>
    void add_component(T* component) {
        if (get_component<T>() != nullptr) {
            delete get_component<T>();
        }

        components[T::id] = dynamic_cast<Component*>(component);
    }

    template <typename T>
    void add_component(Component* component) {
        assert(dynamic_cast<T*>(component) != nullptr);

        if (get_component<T>() != nullptr) {
            delete get_component<T>();
        }

        components[T::id] = component;
    }

    template <typename T>
    T* get_component() {
        std::string id = T::id;
        if (components.find(id) != components.end()) {
            return dynamic_cast<T*>(components[id]);
        }

        return nullptr;
    }

    template <typename T>
    bool has_component() {
        std::string id = T::id;
        return (components.find(id) != components.end());
    }

    void clear_components() {
        for (std::unordered_map<std::string, Component*>::iterator c = components.begin(); c != components.end(); c++) {
            delete c->second;
        }
        components.clear();
    }

    ~Entity() {
        clear_components();
    }
};

#endif //HEXGAME_ENTITY_HPP
