#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Rook : public Piece
{
public:
    Rook(const std::string &color, const int xPosition, const int yPosition, const std::string name);

    Rook *clone() const override
    {
        return new Rook(*this); // Copy constructor
    }

    ~Rook() override = default;

    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;

private:
    std::string blackGraphic = "assets/br.png";
    std::string whiteGraphic = "assets/wr.png";
};

#endif