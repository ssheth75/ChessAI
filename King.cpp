#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "King.hpp"
#include "Board.hpp"
#include <iostream>

King::King(Player color, const int col, const int row, const std::string name) : Piece(color, col, row, name)
{
    std::string textureFile = (color == Player::WHITE) ? "assets/wk.png" : "assets/bk.png";

    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    m_sprite.setTexture(m_texture); // Set the loaded texture to the sprite
}

void checkCastling(Piece *king, int col, int row, const Board &board, std::vector<Move> &moves)
{
    // Array for king-side and queen-side castling offsets
    const std::vector<std::pair<int, int>> castlingOffsets = {
        {3, 2},  // King-side: Rook is 3 squares away, king moves 2 squares
        {-4, -2} // Queen-side: Rook is 4 squares away, king moves 2 squares
    };

    if (!king->hasMoved())
    {
        for (const auto &[rookOffset, kingMoveOffset] : castlingOffsets)
        {
            int rookCol = col;                      // Rook is on the same row as the king
            int rookRow = row + rookOffset;         // Calculate rook position
            int kingDestRow = row + kingMoveOffset; // King's destination after castling

            // Ensure the rook exists and hasn't moved
            if (rookRow >= 0 && rookRow < 8 &&
                board.m_grid[rookCol][rookRow] != nullptr &&
                board.m_grid[rookCol][rookRow]->getType() == "ROOK" &&
                !board.m_grid[rookCol][rookRow]->hasMoved())
            {
                // Check the path between the king and the rook
                bool clearPath = true;
                int step = (rookOffset > 0) ? 1 : -1;
                for (int i = 1; i < abs(rookOffset); ++i)
                {
                    if (board.m_grid[col][row + step * i] != nullptr)
                    {
                        clearPath = false;
                        break;
                    }
                }

                // Check that the king does not pass through or land on attacked squares
                if (clearPath)
                {
                    // Add castling move
                    moves.push_back({king, col, kingDestRow, MoveType::CASTLE}); 
                }
            }
        }
    }
}

std::vector<Move> King::generateMoves(int col, int row, const Board &board) const
{
    std::vector<Move> moves;
    auto king = board.m_grid[col][row];
    Player color = king->m_color;

    // Possible directions the king can move
    std::vector<std::pair<int, int>> directions = {
        {1, 0},   // Down
        {-1, 0},  // Up
        {0, 1},   // Right
        {0, -1},  // Left
        {1, 1},   // Down-right
        {-1, -1}, // Up-left
        {-1, 1},  // Up-right
        {1, -1}   // Down-left
    };

    // Check each possible move
    for (const auto &[rowStep, colStep] : directions)
    {
        int newRow = row + rowStep;
        int newCol = col + colStep;

        // Ensure the move is within the bounds of the board
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
        {
            Piece *target = board.m_grid[newCol][newRow];
            if (target == nullptr || target->m_color != color) // Empty or opponent's piece
            {
                moves.push_back({king, newCol, newRow, MoveType::NORMAL}); // normal move
            }
        }
    }

    // Castling

    const auto &pieces = (color == Player::BLACK ? board.m_blackPieces : board.m_whitePieces);

    checkCastling(king, col, row, board, moves);

    return moves;
}

std::string King::getType() const
{
    return m_type;
}
