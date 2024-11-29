#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Knight : public Piece
{
public:
    Knight(Player color, const int col, const int row, const std::string name);

    Knight *clone() const override
    {
        return new Knight(*this); // Copy constructor
    }

    ~Knight() override = default;

    const std::string m_type = "NIGHT";

    int getVal() const override;

private:
    std::string getType() const override;
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
};

#endif