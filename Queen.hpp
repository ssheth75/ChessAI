#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Queen : public Piece
{
public:
    Queen(const std::string &color, const int xPosition, const int yPosition);

    ~Queen() override = default;

    std::vector<Move> generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/bq.png";
std::string whiteGraphic = "assets/wq.png";
};

#endif