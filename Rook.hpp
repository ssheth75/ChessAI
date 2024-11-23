#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Rook : public Piece
{
public:
    Rook(Player color, const int col, const int row, const std::string name);

    Rook *clone() const override
    {
        return new Rook(*this); 
    }

    ~Rook() override = default;

private:
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;
};

#endif