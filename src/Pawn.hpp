#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include <vector>
#include "util.hpp"

class Pawn : public Piece
{
public:
    Pawn(Player color, const int xPosition, const int yPosition, const std::string name);

    Pawn *clone() const override
    {
        return new Pawn(*this); // Copy constructor
    }

    ~Pawn() override = default;

    const std::string m_type = "PAWN";

    bool hasMoved() const override { return m_moved; }
    void setMoved(bool moved) override { this->m_moved = moved; }
    bool m_moved = false;
    int getVal() const override; // Pure virtual function

private:
    std::vector<Move> generateMoves(int col, int row, const Board &board) const override;
    std::string getType() const override;
};

#endif