#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "util.hpp"
#include "Piece.hpp"
#include <vector>

class Bishop : public Piece
{
public:
    Bishop(const std::string &color, const int xPosition, const int yPosition, const std::string name);

    ~Bishop() override = default;

    Bishop *clone() const override
    {
        return new Bishop(*this); // Copy constructor
    }

    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/bb.png";
    std::string whiteGraphic = "assets/wb.png";
};

#endif