#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Bishop : public Piece
{
public:
    Bishop(const std::string &color, const int xPosition, const int yPosition);

    ~Bishop() override = default;

    std::vector<Move> generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/bb.png";
std::string whiteGraphic = "assets/wb.png";
};

#endif