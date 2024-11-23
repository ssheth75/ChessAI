#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class King : public Piece
{
public:
    King(const std::string &color, const int xPosition, const int yPosition, const std::string name);

    King *clone() const override
    {
        return new King(*this); // Copy constructor
    }

    ~King() override = default;

    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/bk.png";
    std::string whiteGraphic = "assets/wk.png";
};

#endif