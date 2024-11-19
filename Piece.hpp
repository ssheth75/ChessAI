#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <vector>
#include "util.cpp"

class Piece {
public:
    Piece(std::string color);
    virtual ~Piece() {}
    virtual std::vector<Move>generateMoves();

    virtual std::string getType() const = 0;  // Pure virtual function


protected:
    char color;
};

#endif
