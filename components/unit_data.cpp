//
// Created by edoardo biasio on 2021-03-19.
//

#include "unit_data.hpp"

const std::string UnitData::id = "unit_data";

UnitData::UnitData(int hp, int armor, int defence, int dmg, int attack) : hp(hp), total_hp(hp), armor(armor), defence_skill(defence), damage(dmg), attack_skill(attack) {

}

UnitData::UnitData(const UnitData &other, class Entity* owner) : hp(other.hp), total_hp(other.hp), armor(other.armor), defence_skill(other.defence_skill), damage(other.damage), attack_skill(other.attack_skill) {

}

Component* UnitData::parse(std::vector<std::string> buffer, Entity *entity, Game *game) {
    std::string file_path = "";
    int hp = 0, armor = 0, defence = 0, dmg = 0, attack = 0;
    while (!buffer.empty()) {
        std::string line = buffer[0];
        buffer.erase(buffer.begin());
        if (hp == 0)
            hp = parse_segment_i(line, "hp:", 3);

        if (armor == 0)
        armor = parse_segment_i(line, "armor:", 6);

        if (defence == 0)
        defence = parse_segment_i(line, "defence:", 8);

        if (dmg == 0)
        dmg = parse_segment_i(line, "dmg:", 4);

        if (attack == 0)
        attack = parse_segment_i(line, "attack:", 7);
    }

    Component* unit_data = new UnitData(hp, armor, defence, dmg, attack);

    return unit_data;
}

int UnitData::getHp() const {
    return hp;
}

int UnitData::getTotalHp() const {
    return total_hp;
}

int UnitData::getArmor() const {
    return armor;
}

int UnitData::getDefenceSkill() const {
    return defence_skill;
}

int UnitData::getDamage() const {
    return damage;
}

int UnitData::getAttackSkill() const {
    return attack_skill;
}
