#include "pathfind.hpp"

#include <algorithm>
#include <cstdlib>
#include <queue>

struct AStarNode {
    Position pos;
    size_t g;
    size_t f;
};

struct AStarNodeCompare {
    constexpr bool operator()(const AStarNode& a, const AStarNode& b) const { return a.f > b.f; }
};

// Manhattan distance
size_t heuristic(const Position& a, const Position& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Position> pathfind_astar(const Map<128, 128>& map, Piece piece, Position destination) {
    auto key = [](Position p) { return (int64_t)p.x << 32 | (uint32_t)p.y; };

    std::priority_queue<AStarNode, std::vector<AStarNode>, AStarNodeCompare> q;

    std::unordered_map<int64_t, size_t> gscore;
    std::unordered_map<int64_t, Position> parent;

    q.push({piece.position, 0, heuristic(piece.position, destination)});
    gscore[key(piece.position)] = 0;

    while(!q.empty()) {
        AStarNode cur = q.top();
        q.pop();

        if(gscore.contains(key(cur.pos)) && cur.g > (size_t)gscore[key(cur.pos)]) {
            continue;
        }

        if(cur.pos == destination) {
            return reconstruct_astar(parent, destination);
        }

        piece.position = cur.pos;

        std::set<Position> next_positions = piece.generate_movable_positions(map);
        for(const auto& p : next_positions) {
            size_t tentative_g = cur.g + 1;
            auto k = key(p);

            if(!gscore.contains(k) || tentative_g < gscore[k]) {
                parent[k] = cur.pos;
                gscore[k] = tentative_g;

                size_t f = tentative_g + heuristic(p, destination);
                q.push({p, tentative_g, f});
            }
        }
    }

    return {};
}

std::vector<Position> reconstruct_astar(std::unordered_map<int64_t, Position>& parent,
                                        Position current) {
    std::vector<Position> path;

    auto key = [](Position p) { return (int64_t)p.x << 32 | (uint32_t)p.y; };

    while(parent.contains(key(current))) {
        path.push_back(current);
        current = parent[key(current)];
    }

    path.push_back(current);
    std::reverse(path.begin(), path.end());

    return path;
}
