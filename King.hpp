#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class King : public Piece
{
public:
    King(Player color, const int col, const int row, const std::string name);

    King *clone() const override
    {
        return new King(*this); // Copy constructor
    }

    ~King() override = default;

private:
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;
};

#endif