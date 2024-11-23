#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Queen : public Piece
{
public:
    Queen(const std::string &color, const int xPosition, const int yPosition, const std::string name);

    Queen *clone() const override
    {
        return new Queen(*this); // Copy constructor
    }
    ~Queen() override = default;

    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/bq.png";
    std::string whiteGraphic = "assets/wq.png";
};

#endif