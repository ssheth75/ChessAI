#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class King : public Piece
{
public:
    King(const std::string &color, const int xPosition, const int yPosition);

    ~King() override = default;

    std::vector<Move> generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/bk.png";
std::string whiteGraphic = "assets/wk.png";
};

#endif