#include "Piece.hpp"
#include <vector>
#include "util.cpp"


class Pawn : Piece {
    public:
    Pawn();

    ~Pawn();

    std::vector<Move> generateMoves(){

    }

    std::string getType() const override{
        return "Pawn";
    }

    private:
};