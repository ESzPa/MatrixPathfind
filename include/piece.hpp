#pragma once

#include <cstdint>
#include <set>
#include <vector>

#include "matrix.hpp"

template <size_t Y, size_t X>
using Map = FlatMatrix<bool, Y, X>;

struct Position {
    int64_t x;
    int64_t y;
};

struct Move {
    int64_t dx;
    int64_t dy;

    bool operator<(const Move& other) const { return std::tie(dx, dy) < std::tie(other.dx, other.dy); }
};

// Rule
// -1: Infinite
//  N: Maximum number of steps
struct MoveRule {
    Move move;
    int64_t rule;
};

struct Piece {
    Position position;
    std::vector<MoveRule> rules;

    std::set<Move> generate_moves(const Map<128, 128>& map) const;
};

std::vector<Move> moves_from_rule(const Map<128, 128>& map, MoveRule rule, Position position);
