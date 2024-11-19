#include "Piece.hpp"
#include <vector>
#include "util.cpp"


class Pawn : Piece {
    public:
    Pawn();

    ~Pawn();

    std::vector<Move> generateValidMoves();

    private:
};