#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Knight.hpp"
#include <iostream>
#include "Board.hpp"

Knight::Knight(Player color, const int col, const int row, const std::string name) : Piece(color, col, row, name)
{
    std::string textureFile = (color == Player::WHITE) ? "../assets/wn.png" : "../assets/bn.png";

    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    m_sprite.setTexture(m_texture); // Set the loaded texture to the sprite
}

std::vector<Move> Knight::generateMoves(int col, int row, const Board &board) const
{
    std::vector<Move> moves;
    auto piece = board.m_grid[col][row];
    Player color = piece->m_color;

    // All possible moves for a knight
    std::vector<std::pair<int, int>> knightMoves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, // Vertical L-shapes
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2} // Horizontal L-shapes
    };

    // Check each possible move
    for (const auto &[rowStep, colStep] : knightMoves)
    {
        int newRow = row + rowStep;
        int newCol = col + colStep;

        // Ensure the move is within the bounds of the board
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
        {
            Piece *target = board.m_grid[newCol][newRow];
            if (target == nullptr || target->m_color != color) // Empty or opponent's piece
            {
                moves.push_back({piece, newCol, newRow, MoveType::NORMAL}); //normal move
            }
        }
    }

    return moves;
}

std::string Knight::getType() const
{
    return m_type;
}
