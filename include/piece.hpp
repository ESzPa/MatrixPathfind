#pragma once

#include <cstdint>
#include <set>
#include <vector>

#include "matrix.hpp"

template <size_t Y, size_t X>
using Map = FlatMatrix<bool, Y, X>;

struct Position {
    int32_t x;
    int32_t y;

    constexpr bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    constexpr bool operator<(const Position& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

struct Move {
    int32_t dx;
    int32_t dy;

    constexpr bool operator<(const Move& other) const {
        return std::tie(dx, dy) < std::tie(other.dx, other.dy);
    }
};

// Rule
// -1: Infinite
//  N: Maximum number of steps
struct MoveRule {
    Move move;
    int32_t rule;
};

struct Piece {
    Position position;
    std::vector<MoveRule> rules;

    std::set<Position> generate_movable_positions(const Map<128, 128>& map) const;
};

std::vector<Position> positions_from_rule(const Map<128, 128>& map, MoveRule rule, Position position);
