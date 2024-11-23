#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Knight : public Piece
{
public:
    Knight(const std::string &color, const int xPosition, const int yPosition, const std::string name);

    Knight *clone() const override
    {
        return new Knight(*this); // Copy constructor
    }

    ~Knight() override = default;

    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/bn.png";
    std::string whiteGraphic = "assets/wn.png";
};

#endif