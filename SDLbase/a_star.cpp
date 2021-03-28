//
// Created by edoardo biasio on 2021-03-05.
//

#include "a_star.hpp"
#include "../game.hpp"

Game* AStar::game = nullptr;

void AStar::set_game(Game *game_) {
    game = game_;
}

bool AStar::is_valid(int x, int y) {
    int id = x + y * game->get_map_size().x;
    HexMap* map = game->get_hex_map();
    return map->check_boundaries(x, y) && !map->get_tile_at_index(x, y)->blocks;
}

bool AStar::is_destination(int x, int y, Node destination) {
    return x == destination.x && y == destination.y;
}

double AStar::calculate_h(int x, int y, Node destination) {
    double H = (sqrt((x - destination.x) * (x - destination.x) + (y - destination.y) * (y - destination.y)));
    return H;
}

std::vector<Node> AStar::a_star(Node player, Node destination) {
    std::vector<Node> empty;
    if (!is_valid(destination.x, destination.y)) {
        //std::cerr << "Destination is an obstacle" << std::endl;
        return empty;
    }
    if (is_destination(player.x, player.y, destination)) {
        //std::cerr << "Destination is player" << std::endl;
        return empty;
    }

    bool closed_list[game->get_map_size().x][game->get_map_size().y];

    const Vector2<int> map_size = game->get_map_size();
    std::array< std::array < Node, 12 >, 26 > map {0};
    //std::vector< std::vector <Node> > map;
    //map.reserve(map_size.x);
    for (int x = 0; x < map_size.x; x++) {
        //map[x].reserve(map_size.y);
        for (int y = 0; y < map_size.y; y++) {
	    
	        //map[x].emplace_back(Node());
            map[x][y].f_cost = FLT_MAX;
            map[x][y].g_cost = FLT_MAX;
            map[x][y].h_cost = FLT_MAX;
            map[x][y].parent_x = -1;
            map[x][y].parent_y = -1;
            map[x][y].x = x;
            map[x][y].y = y;

            closed_list[x][y] = false;
        }
    }

    int x = player.x;
    int y = player.y;
    map[x][y].f_cost = 0.0;
    map[x][y].g_cost = 0.0;
    map[x][y].h_cost = 0.0;
    map[x][y].parent_x = x;
    map[x][y].parent_y = y;

    std::vector<Node> open_list;
    open_list.emplace_back(map[x][y]);
    bool destination_found = false;

    while (!open_list.empty() && open_list.size() < map_size.x * map_size.y) {
        Node node;

        do {
            float temp = FLT_MAX;
            std::vector<Node>::iterator it_node;
            for (auto it = open_list.begin(); it != open_list.end(); it = std::next(it)) {
                Node n = *it;
                if (n.f_cost < temp) {
                    temp = n.f_cost;
                    it_node = it;
                }
            }

            node = *it_node;
            open_list.erase(it_node);
        } while (!is_valid(node.x, node.y) && open_list.size() > 0);

        x = node.x;
        y = node.y;

        closed_list[x][y] = true;

        for (int new_x = -1; new_x <= 1; new_x++) {
            for (int new_y = -1; new_y <= 1; new_y++) {
                //if (new_x == -1 && new_y == -1) continue;
                if (new_x * new_y != 0) continue;
                double g_new, h_new, f_new;
                if (is_valid(x + new_x, y + new_y)) {
                    if (is_destination(x + new_x, y + new_y, destination)) {
                        map[x + new_x][y + new_y].parent_x = x;
                        map[x + new_x][y + new_y].parent_y = y;
                        destination_found = true;
                        return make_path(map, destination);
                    } else if (!closed_list[x + new_x][y + new_y]) {
                        g_new = node.g_cost + 1.0;
                        h_new = calculate_h(x + new_x, y + new_y, destination);
                        f_new = g_new + h_new;

                        if (map[x + new_x][y + new_y].f_cost == FLT_MAX || map[x + new_x][y + new_y].f_cost > f_new) {
                            map[x + new_x][y + new_y].f_cost = f_new;
                            map[x + new_x][y + new_y].g_cost = g_new;
                            map[x + new_x][y + new_y].h_cost = h_new;
                            map[x + new_x][y + new_y].parent_x = x;
                            map[x + new_x][y + new_y].parent_y = y;
                            open_list.emplace_back(map[x + new_x][y + new_y]);
                        }
                    }
                }
            }
        }

    }
    if (destination_found == false) {
        std::cout << "Destination not found" << std::endl;
        return empty;
    }
    return empty;
}


std::vector<Node> AStar::make_path(std::array< std::array < Node, 12 >, 26 > map, Node destination) {
    try {
        //std::cout << "found a path" << std::endl;
        int x = destination.x;
        int y = destination.y;
        std::stack<Node> path;
        std::vector<Node> usable_path;

        while (!(map[x][y].parent_x == x && map[x][y].parent_y == y) && map[x][y].x != -1 && map[x][y].y != -1) {
            path.push(map[x][y]);
            int temp_x = map[x][y].parent_x;
            int temp_y = map[x][y].parent_y;
            x = temp_x;
            y = temp_y;
        }

        path.push(map[x][y]);

        while (!path.empty()) {
            Node top = path.top();
            path.pop();
            usable_path.emplace_back(top);
        }

        return usable_path;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return std::vector<Node>();
}
