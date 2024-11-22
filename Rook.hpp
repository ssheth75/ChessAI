#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Rook : public Piece
{
public:
    Rook(const std::string &color, const int xPosition, const int yPosition);

    ~Rook() override = default;

    std::vector<Move> generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/br.png";
std::string whiteGraphic = "assets/wr.png";
};

#endif