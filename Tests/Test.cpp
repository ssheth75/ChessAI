#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Knight.hpp"
#include <iostream>
#include "Board.hpp"
#include "Test.hpp"

std::string Test::generateFEN(const std::vector<std::vector<Piece *>> &grid)
{

    std::string fen;

    for (int row = 0; row < 8; ++row)
    {
        int emptyCount = 0;
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = grid[row][col];
            if (piece == nullptr)
            {
                ++emptyCount;
            }
            else
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                char pieceChar = piece->getType()[0]; // Assuming `getType` returns "Pawn", "Rook", etc.
                if (piece->m_color == Player::BLACK)
                {
                    pieceChar = std::tolower(pieceChar);
                }
                fen += pieceChar;
            }
        }
        if (emptyCount > 0)
        {
            fen += std::to_string(emptyCount);
        }
        if (row < 7)
        {
            fen += '/';
        }
    }

    return fen;
}
