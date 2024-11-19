#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class King : public Piece
{
public:
    King(const std::string &color);

    ~King() override = default;

    std::vector<Move> generateMoves(uint32_t row, uint32_t col, const std::vector<std::vector<Piece *>> &grid) const override;
    std::string getType() const override;

private:
std::string blackGraphic = "assets/bk.png";
std::string whiteGraphic = "assets/wk.png";
};

#endif