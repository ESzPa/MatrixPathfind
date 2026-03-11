#pragma once

#include <unordered_map>
#include <vector>

#include "piece.hpp"

// Start is at the piece position
std::vector<Position> pathfind_astar(const FMap& map, Piece piece, Position destination,
                                     FMap* visited = nullptr);
std::vector<Position> reconstruct_astar(std::unordered_map<int64_t, Position>& parent, Position current);
