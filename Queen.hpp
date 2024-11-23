#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Queen : public Piece
{
public:
    Queen(Player color, const int xPosition, const int yPosition, const std::string name);

    Queen *clone() const override
    {
        return new Queen(*this); // Copy constructor
    }
    ~Queen() override = default;

private:
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;
};

#endif