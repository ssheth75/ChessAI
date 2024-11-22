#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Knight : public Piece
{
public:
    Knight(const std::string &color, const int xPosition, const int yPosition);

    ~Knight() override = default;

    std::vector<Move> generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/bn.png";
std::string whiteGraphic = "assets/wn.png";
};

#endif