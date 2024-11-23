#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "util.hpp"
#include "Piece.hpp"
#include <vector>

class Bishop : public Piece
{
public:
    Bishop(Player color, const int col, const int row, const std::string name);

    ~Bishop() override = default;

    Bishop *clone() const override
    {
        return new Bishop(*this); // Copy constructor
    }


private:
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

};

#endif