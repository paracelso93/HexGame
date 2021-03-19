//
// Created by edoardo biasio on 2021-03-19.
//

#ifndef HEXGAME_UNIT_DATA_HPP
#define HEXGAME_UNIT_DATA_HPP


#include "../component.hpp"
#include <string>
#include <vector>

class UnitData : public Component {
private:
    int hp;
    int total_hp;
    int armor;
    int defence_skill;
    int damage;
    int attack_skill;

public:
    UnitData(int hp, int armor, int defence, int dmg, int attack);
    UnitData(const UnitData& other, class Entity* owner);
    void update(float dt) override {}
    static Component* parse(std::vector<std::string> buffer, class Entity* entity, class Game* game);

    static int parse_segment_i(const std::string& line, const std::string& value, int size) {
        if (line.find(value) != std::string::npos) {
            std::string val = line.substr(size);
            return std::stoi(val);
        }

        return 0;
    }

    int getHp() const;

    int getTotalHp() const;

    int getArmor() const;

    int getDefenceSkill() const;

    int getDamage() const;

    int getAttackSkill() const;

    static const std::string id;
};


#endif //HEXGAME_UNIT_DATA_GUI_HPP
