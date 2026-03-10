#include "piece.hpp"

std::set<Position> Piece::generate_movable_positions(const Map<128, 128>& map) const {
    std::set<Position> newpos;
    for(MoveRule rule : rules) {
        std::vector<Position> pos = positions_from_rule(map, rule, position);
        newpos.insert(pos.begin(), pos.end());
    }
    return newpos;
}

std::vector<Position> positions_from_rule(const Map<128, 128>& map, MoveRule rule, Position position) {
    auto invalid = [&map](int32_t x, int32_t y) {
        return (x >= map.width() || y >= map.height() || x < 0 || y < 0 || map[y, x]);
    };

    std::vector<Position> pos;

    int32_t limit = rule.rule < 0 ? INT32_MAX : rule.rule;

    for(int32_t i = 1; i <= limit; ++i) {
        Position newpos{position.x + rule.move.dx * i, position.y + rule.move.dy * i};

        if(invalid(newpos.x, newpos.y)) {
            break;
        }

        pos.push_back(newpos);
    }

    return pos;
}
