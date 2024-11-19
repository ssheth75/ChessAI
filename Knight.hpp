#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Knight : public Piece
{
public:
    Knight(const std::string &color);

    ~Knight() override = default;

    std::vector<Move> generateMoves(uint32_t row, uint32_t col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/bn.png";
std::string whiteGraphic = "assets/wn.png";
};

#endif