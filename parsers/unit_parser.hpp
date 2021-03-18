//
// Created by edoardo biasio on 2021-03-14.
//

#ifndef HEXGAME_UNIT_PARSER_HPP
#define HEXGAME_UNIT_PARSER_HPP

#include "../entity.hpp"
#include "../component.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <string>
#include "../components/hex.hpp"
#include "../components/transform.hpp"

class UnitParser {
private:
    struct Unit {
        std::string type;
        std::vector<Component* > components;
        std::string id;
    };
    static std::vector<Unit* > units;
    static std::vector<std::string > unit_types;
    static bool check_line_with_string(std::string to_search, std::string line) {
        return (to_search.find(line) != std::string::npos);
    }

public:
    static void init() {

        unit_types.emplace_back("land_unit");
    }

    template <typename ...args>
    static Entity* create_entity_from_unit(Unit* unit) {
        Entity* entity = new Entity(unit->id);
        int j = 0;
        for (int i = 0; i < unit->components.size(); i++) {
            std::vector<Component* > components;
            components.push_back(unit->components[i]);
            add_components<args...>(entity, components, j);
            j = 0;
            components.clear();
        }
        return entity;
    }

    static Unit* get_unit_with_id(const std::string& id) {
        for (auto unit : units) {
            if (unit->id == id) {
                return unit;
            }
        }
        return nullptr;
    }

    template <typename ...args>
    static typename std::enable_if<sizeof...(args) == 0>::type add_components(Entity* entity, std::vector<Component*>& components, int& index) {
        if (index >= components.size()) return;
        std::cout << "Error couldn't find type of component at index: " << index << std::endl;
    }

    template <typename T, typename ...args>
    static void add_components(Entity* entity, std::vector<Component*>& components, int& index) {
        if (index >= components.size()) return;
        auto new_component = dynamic_cast<T*>(components[index]);
        if (new_component == nullptr) {
            add_components<args...>(entity, components, index);
            return;
        } else {
            Component* c = new T(*new_component, entity);
            add_component<T>(entity, c);
            index++;

            //std::cout << "found with type " << T::id << std::endl;
            add_components<args...>(entity, components, index);
        }
    }

    template <typename ...args>
    static typename std::enable_if<sizeof...(args) == 0>::type parse_component_with_id(const std::string& id, std::vector<std::string> buffer, Entity* entity, class Game* game, std::vector<Component* >& components) {
        std::cout << "id: " << id << " is not valid" << std::endl;
    }

    template <typename T, typename ...args>
    static void parse_component_with_id(const std::string& id, std::vector<std::string> buffer, Entity* entity, class Game* game, std::vector<Component* >& components) {
        Component* component = nullptr;
        if (T::id == id) {
            component = T::parse(buffer, entity, game);
            add_component<T>(entity, component);
            components.push_back(component);
        } else {
            parse_component_with_id<args...>(id, buffer, entity, game, components);
        }
    }

    /*template <typename ...args>
    static void add_components(Entity* entity, std::vector<Component*>& components, int& index, bool b) {
        add_components<args...>(entity, components, index);
    }*/

    template <typename T>
    static void add_component(Entity* entity, Component* component) {
        entity->add_component<T>(component);
    }

    template <typename ... Components>
    static std::vector<Entity* > parse(const std::string& file_path, class Game* game) {
        std::ifstream file(file_path);
        std::string line;
        bool reading_unit = false;
        std::vector<Entity *> entities;
        Unit *current_unit = nullptr;
        Entity* current_entity = nullptr;

        while (file) {
            std::getline(file, line);
            if (line.empty()) {
                continue;
            }

            if (line.substr(0, 2) == "//") {
                continue;
            }

            for (const auto &type : unit_types) {
                if (check_line_with_string(line, "@" + type)) {
                    if (reading_unit) {
                        std::cerr << "error, unit didn't finish" << std::endl;
                        return entities;
                    } else {
                        reading_unit = true;
                        current_unit = new Unit();
                        current_unit->type = type;
                        current_entity = new Entity("", true);
                        continue;
                    }
                }
            }

            if (reading_unit) {
                if (check_line_with_string(line, "id:")) {
                    current_unit->id = line.substr(3);
                    current_entity->set_type_id(current_unit->id);
                }

                if (check_line_with_string(line, "start_component(")) {
                    std::string command = "start_component(";
                    std::string name = line.substr(command.length());
                    name.pop_back();
                    std::vector<std::string> buffer;
                    while (line != "end_component()") {
                        std::getline(file, line);
                        if (line.empty()) {
                            continue;
                        }

                        if (line.substr(0, 2) == "//") {
                            continue;
                        }

                        buffer.push_back(line);
                    }
                    parse_component_with_id<Components...>(name, buffer, current_entity, game, current_unit->components);
                }

                if (check_line_with_string(line, "end_unit")) {
                    reading_unit = false;

                    int i = 0;
                    //add_components<Components...>(current_entity, current_unit->components, i);
                    units.push_back(current_unit);
                    entities.push_back(current_entity);
                }
            }
        }

        return entities;
    }
};


#endif //HEXGAME_UNIT_PARSER_HPP
