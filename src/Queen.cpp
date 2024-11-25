#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Queen.hpp"
#include "Board.hpp"
#include <iostream>

Queen::Queen(Player color, const int col, const int row, const std::string name) : Piece(color, col, row, name)
{
    std::string textureFile = (color == Player::WHITE) ? "../assets/wq.png" : "../assets/bq.png";

    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    m_sprite.setTexture(m_texture); // Set the loaded texture to the sprite
}

std::vector<Move> Queen::generateMoves(int col, int row, const Board &board) const
{
    std::vector<Move> moves;
    Player color = board.m_grid[col][row]->m_color;

    board.checkStarMoves(row, col, -1, 0, moves, color); // Check left
    board.checkStarMoves(row, col, 1, 0, moves, color);  // Check right
    board.checkStarMoves(row, col, 0, 1, moves, color);  // Check below
    board.checkStarMoves(row, col, 0, -1, moves, color); // Check above

    // Check diagonals
    board.checkStarMoves(row, col, -1, 1, moves, color);
    board.checkStarMoves(row, col, 1, -1, moves, color);
    board.checkStarMoves(row, col, 1, 1, moves, color);
    board.checkStarMoves(row, col, -1, -1, moves, color);

    return moves;
}

std::string Queen::getType() const
{
    return m_type;
}
