#pragma once

#include <unordered_map>
#include <vector>

#include "piece.hpp"

// Start is at the piece position
std::vector<Position> pathfind_astar(const Map<128, 128>& map, Piece piece, Position destination);
std::vector<Position> reconstruct_astar(std::unordered_map<int64_t, Position>& parent, Position current);
