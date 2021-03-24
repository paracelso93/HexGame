#include "attacker.hpp"
#include "../entity.hpp"
#include "unit_data.hpp"
#include "../game.hpp"

const std::string Attacker::id = "attacker";

Attacker::Attacker(Entity* owner) : owner(owner) {
    assert(owner->has_component<UnitData>());
    owner_data = owner->get_component<UnitData>();
}

Attacker::Attacker(const Attacker& other, Entity* owner) : owner(owner) {
    assert(owner->has_component<UnitData>());
    owner_data = owner->get_component<UnitData>();
}

int Attacker::attack(Entity* target) {
    assert(target->has_component<UnitData>());
    auto target_data = target->get_component<UnitData>();
    RandomHandler* random = RandomHandler::get_instance();
    int attack = random->get_random_in_range(1, 6);
    attack += owner_data->get_attack_skill();    
    attack -= target_data->get_defence_skill();
    if (attack > 4) {
        int damage = owner_data->get_damage();
        damage -= target_data->get_armor();
        if (damage <= 0) return 0;
        int crit = random->get_random_in_range(1, 6);
        if (crit == 6) damage *= 2;
        
        return damage;
    }
    return 0;
}

void Attacker::defend(int damage) {
    if (damage >= owner_data->get_hp()) {
        owner_data->set_hp(0);
        return;
    }
    
    owner_data->set_hp(owner_data->get_hp() - damage);
}

Component* Attacker::parse(std::vector<std::string> buffer, Entity* entity, Game* game) {
    Component* c = new Attacker(entity);
    return c;
}

