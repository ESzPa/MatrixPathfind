#include "piece.hpp"

std::set<Move> Piece::generate_moves(const Map<128, 128>& map) const {
    std::set<Move> moveset;
    for(MoveRule rule : rules) {
        std::vector<Move> moves = moves_from_rule(map, rule, position);
        moveset.insert(moves.begin(), moves.end());
    }
    return moveset;
}

std::vector<Move> moves_from_rule(const Map<128, 128>& map, MoveRule rule, Position position) {
    auto out_of_bound = [&map](int64_t x, int64_t y) {
        return (x >= map.width() || y >= map.height() || x < 0 || y < 0);
    };

    std::vector<Move> moves;

    int64_t limit = rule.rule < 0 ? INT64_MAX : rule.rule;

    for(int64_t i = 1; i <= limit; ++i) {
        Position newpos{position.x + rule.move.dx * i, position.y + rule.move.dy * i};

        if(out_of_bound(newpos.x, newpos.y))
            break;

        moves.push_back({rule.move.dx * i, rule.move.dy * i});
    }

    return moves;
}
