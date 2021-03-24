//
// Created by edoardo biasio on 2021-03-24.
//

#ifndef HEXGAME_RANDOM_HANDLER_HPP
#define HEXGAME_RANDOM_HANDLER_HPP

#include <random>
#include <unordered_map>
#include <iostream>

class RandomHandler {
private:
    static RandomHandler* instance;
    std::unordered_map<std::pair<int, int>*, std::uniform_int_distribution<int>* >* distributions;
public:
    static RandomHandler* get_instance() {
        if (instance == nullptr) {
            instance = new RandomHandler();
        }

        return instance;
    }

    int get_random_in_range(int min, int max);

    RandomHandler() {
        distributions = new std::unordered_map<std::pair<int, int>*, std::uniform_int_distribution<int>* >();

    }
};


#endif //HEXGAME_RANDOM_HANDLER_HPP
