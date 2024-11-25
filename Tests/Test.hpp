#include "Board.hpp"
#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "King.hpp"
#include "Board.hpp"
#include <iostream>

class Test
{
    Test();

    std::string generateFEN(const std::vector<std::vector<Piece *>> &grid);

    char fenChar(PieceType type);
};
