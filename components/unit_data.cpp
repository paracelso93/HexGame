//
// Created by edoardo biasio on 2021-03-19.
//

#include "unit_data.hpp"

const std::string UnitData::id = "unit_data";

UnitData::UnitData(int hp, int armor, int defence, int dmg, int attack) : hp(hp), total_hp(hp), armor(armor), defence_skill(defence), damage(dmg), attack_skill(attack) {

}

UnitData::UnitData(const UnitData &other, class Entity* owner) : hp(other.hp), total_hp(other.hp), armor(other.armor), defence_skill(other.defence_skill), damage(other.damage), attack_skill(other.attack_skill), description(other.description) {

}

Component* UnitData::parse(std::vector<std::string> buffer, Entity *entity, Game *game) {
    std::string file_path = "";
    std::string description = "";
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

        if (description.empty()) {
            if (line.find("description:") != std::string::npos) {
                std::string val = line.substr(12);
                description = val;
            }
        }
    }

    Component* unit_data = new UnitData(hp, armor, defence, dmg, attack);
    if (!description.empty()) {
        dynamic_cast<UnitData*>(unit_data)->set_description(description);
    }
    return unit_data;
}

void UnitData::set_description(const std::string &description) {
    this->description = description;
}

int UnitData::get_hp() const {
    return hp;
}

int UnitData::get_total_hp() const {
    return total_hp;
}

int UnitData::get_armor() const {
    return armor;
}

int UnitData::get_defence_skill() const {
    return defence_skill;
}

int UnitData::get_damage() const {
    return damage;
}

int UnitData::get_attack_skill() const {
    return attack_skill;
}

const std::string& UnitData::get_description() const {
    return description;
}
