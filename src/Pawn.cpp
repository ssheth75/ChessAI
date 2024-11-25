#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Pawn.hpp"
#include "Board.hpp"
#include <iostream>

Pawn::Pawn(Player color, const int col, const int row, const std::string name) : Piece(color, col, row, name)
{
    std::string textureFile = (color == Player::WHITE) ? "../assets/wp.png" : "../assets/bp.png";

    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    m_sprite.setTexture(m_texture); // Set the loaded texture to the sprite
}

bool checkPromotion(Player color, int col)
{
    int promotionRank = (color == Player::BLACK ? 7 : 0);
    if (col == promotionRank)
        return true;
    return false;
}

// col is first and row is second. col = x; row = y; board uses this and is the same as cartesian
std::vector<Move> Pawn::generateMoves(int col, int row, const Board &board) const
{
    std::vector<Move> moves;
    Player color = board.m_grid[col][row]->m_color;

    // Direction: +1 for black, -1 for white
    int direction = (color == Player::WHITE) ? -1 : 1;

    auto piece = board.m_grid[col][row];

    // Forward Move
    if (col + direction >= 0 && col + direction < 8 && board.m_grid[col + direction][row] == nullptr)
    {
        if (checkPromotion(color, col + direction))
        {
            moves.push_back({piece, col + direction, row, MoveType::PROMOTION}); // Single forward move
        }
        else
        {
            moves.push_back({piece, col + direction, row, MoveType::NORMAL}); // Single forward move
        }
        // Double Forward Move (only from starting position)
        if ((color == Player::WHITE && col == 6) || (color == Player::BLACK && col == 1))
        {
            if (board.m_grid[col + 2 * direction][row] == nullptr)
            {
                moves.push_back({piece, col + (2 * direction), row, MoveType::NORMAL});
                // std::cout << col + (2 * direction) << std::endl;
                // std::cout << row << std::endl;
            }
        }
    }

    // Capture Left
    if (row - 1 >= 0 && col + direction >= 0 && col + direction < 8)
    {
        Piece *target = board.m_grid[col + direction][row - 1];
        if (target != nullptr && target->m_color != color)
        {
            if (checkPromotion(color, col + direction))
            {
                moves.push_back({piece, col + direction, row - 1, MoveType::PROMOTION});
            }
            else
            {
                moves.push_back({piece, col + direction, row - 1, MoveType::NORMAL}); // Diagonal capture left
            }
        }
    }

    // Capture Right
    if (row + 1 < 8 && col + direction >= 0 && col + direction < 8)
    {
        Piece *target = board.m_grid[col + direction][row + 1];
        if (target != nullptr && target->m_color != color)
        {
            if (checkPromotion(color, col + direction))
            {
                moves.push_back({piece, col + direction, row + 1, MoveType::PROMOTION}); // Diagonal capture right
            }
            else
            {
                moves.push_back({piece, col + direction, row + 1, MoveType::NORMAL}); // Diagonal capture right
            }
        }
    }

    // Check pawn promotion

    return moves;

    // Implement en passant later
}

std::string Pawn::getType() const
{
    return m_type;
}
