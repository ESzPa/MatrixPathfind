#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "pathfind.hpp"
#include "piece.hpp"

void basic_print(const Map<128, 128>& map, const std::vector<Position>& path);

int main(int argc, char** argv) {
    Map<128, 128> map;

    if(argc > 1) {
        std::ifstream file(argv[1]);
        if(!file) {
            return 1;
        }

        std::string line;
        size_t y = 0;
        while(std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            std::vector<int> row;

            while(std::getline(ss, cell, '\t')) {
                row.push_back(std::stoi(cell));
            }

            for(size_t x = 0; x < map.width(); ++x) {
                map[y, x] = row[x] == 1;
            }

            ++y;
        }
    }
    else {
        std::random_device rd;
        std::mt19937 rng(rd());

        // 75% space, 25% wall
        std::vector<double> weights = {75, 25};

        std::discrete_distribution<int> dist(weights.begin(), weights.end());

        auto ranbool = [&dist, &rng]() { return dist(rng); };

        for(size_t y = 0; y < map.height(); ++y) {
            for(size_t x = 0; x < map.width(); ++x) {
                map[y, x] = ranbool();
            }
        }
    }

    return 0;
}

void basic_print(const Map<128, 128>& map, const std::vector<Position>& path) {
    std::set<Position> path_set(path.begin(), path.end());

    for(size_t y = 0; y < map.height(); ++y) {
        for(size_t x = 0; x < map.width(); ++x) {
            Position p{(int32_t)x, (int32_t)y};

            if(!path.empty() && p == path.front()) {
                std::cout << "\033[32mS \033[0m";
            }
            else if(!path.empty() && p == path.back()) {
                std::cout << "\033[31mE \033[0m";
            }
            else if(path_set.contains(p)) {
                std::cout << "\033[33m* \033[0m";
            }
            else if(map[y, x]) {
                std::cout << "# ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << '\n';
    }
}
