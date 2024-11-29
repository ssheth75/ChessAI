#include "util.hpp"
#include "Piece.hpp"
#include <vector>
#include "Rook.hpp"
#include "Board.hpp"
#include <iostream>

Rook::Rook(Player color, const int col, const int row, const std::string name) : Piece(color, col, row, name)
{
    std::string textureFile = (color == Player::WHITE) ? "../assets/wr.png" : "../assets/br.png";

    if (!m_texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    m_sprite.setTexture(m_texture); // Set the loaded texture to the sprite
}

std::vector<Move> Rook::generateMoves(int col, int row, const Board &board) const
{

    std::vector<Move> potentialMoves;
    Player color = board.m_grid[col][row]->m_color;

    // Check left, right, up, down
    checkStarMoves(row, col, -1, 0, potentialMoves, color, board); // Check left
    checkStarMoves(row, col, 1, 0, potentialMoves, color, board);  // Check right
    checkStarMoves(row, col, 0, 1, potentialMoves, color, board);  // Check above
    checkStarMoves(row, col, 0, -1, potentialMoves, color, board); // Check below

    // add castling

    return potentialMoves;
}

std::string Rook::getType() const
{
    return m_type;
}

int Rook::getVal() const
{
    return 3;
}
