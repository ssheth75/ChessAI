#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Pawn : public Piece
{
public:
    Pawn(const std::string &color, const int xPosition, const int yPosition);

    ~Pawn() override = default;

    std::vector<Move> generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/bp.png";
    std::string whiteGraphic = "assets/wp.png";
};

#endif