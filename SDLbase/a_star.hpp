//
// Created by edoardo biasio on 2021-03-05.
//

#ifndef HEXGAME_A_STAR_HPP
#define HEXGAME_A_STAR_HPP

#include <vector>
#include <array>
#include <stack>

struct Node {
    int x, y;
    int parent_x, parent_y;
    float g_cost;
    float h_cost;
    float f_cost;
};

inline static bool operator < (const Node& lhs, const Node& rhs) {
    return lhs.f_cost < rhs.f_cost;
}

class AStar {
private:
    static class Game* game;

public:
    static void set_game(class Game* game_);
    static bool is_valid(int x, int y);
    static bool is_destination(int x, int y, Node destination);
    static double calculate_h(int x, int y, Node destination);
    static std::vector<Node> a_star(Node player, Node destination);
    static std::vector<Node> make_path(std::array < std::array <Node, 12>, 26> map, Node destination);
};


#endif //HEXGAME_A_STAR_HPP
