#include "util.hpp"
#include "Piece.hpp"
#include <vector>
#include "Bishop.hpp"
#include "Board.hpp"
#include <iostream>

Bishop::Bishop(Player color, const int col, const int row, const std::string name) : Piece(color, col, row, name)
{
    std::string textureFile = (color == Player::WHITE) ? "../assets/wb.png" : "../assets/bb.png";

    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    m_sprite.setTexture(m_texture); // Set the loaded texture to the sprite
}

std::vector<Move> Bishop::generateMoves(int col, int row, const Board &board) const
{
    Player color = board.m_grid[col][row]->m_color;


    // Check diagonals for potential moves
    std::vector<Move> moves;
    checkStarMoves(row, col, -1, 1, moves, color, board);
    checkStarMoves(row, col, 1, -1, moves, color, board);
    checkStarMoves(row, col, 1, 1, moves, color, board);
    checkStarMoves(row, col, -1, -1, moves, color, board);


    return moves;
}

std::string Bishop::getType() const
{
    return m_type;
}

int Bishop::getVal() const
{
    return 3;
}