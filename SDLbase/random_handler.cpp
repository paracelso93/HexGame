//
// Created by edoardo biasio on 2021-03-24.
//

#include "random_handler.hpp"

RandomHandler* RandomHandler::instance = nullptr;

int RandomHandler::get_random_in_range(int min, int max) {
    auto r = new std::pair<int, int>(min, max);
    auto it = distributions->find(r);

    if (it == distributions->end()) {
        //distributions[range] = new std::uniform_int_distribution<int>(min, max);
        distributions->insert(std::make_pair(r, new std::uniform_int_distribution<int>(min, max)));
    }

    std::random_device device;
    std::default_random_engine engine(device());
    return (*distributions->at(r))(engine);
}