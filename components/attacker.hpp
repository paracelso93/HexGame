#ifndef HEXGAME_ATTACKER_HPP
#define HEXGAME_ATTACKER_HPP

#include "../component.hpp"
#include <vector>
#include "../SDLbase/random_handler.hpp"

class Attacker : public Component {
private:
    class Entity* owner;
    class UnitData* owner_data;
    
public:
    static const std::string id;
    Attacker(class Entity* owner);
    void update(float dt) override {}
    int attack(class Entity* target);
    void defend(int damage);
    Attacker(const Attacker& other, class Entity* owner);
    ~Attacker() {}
    static Component* parse(std::vector<std::string> buffer, class Entity* entity, class Game* game);
};

#endif
