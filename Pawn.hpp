#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Pawn : public Piece
{
public:
    Pawn(Player color, const int xPosition, const int yPosition, const std::string name);

    Pawn *clone() const override
    {
        return new Pawn(*this); // Copy constructor
    }

    ~Pawn() override = default;

private:
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;
};

#endif