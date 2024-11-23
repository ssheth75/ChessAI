#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Pawn : public Piece
{
public:
    Pawn(const std::string &color, const int xPosition, const int yPosition, const std::string name);

    Pawn *clone() const override
    {
        return new Pawn(*this); // Copy constructor
    }

    ~Pawn() override = default;

    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/bp.png";
    std::string whiteGraphic = "assets/wp.png";
};

#endif