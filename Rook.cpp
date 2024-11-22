#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Rook.hpp"
#include <iostream>

Rook::Rook(const std::string &color, const int xPosition, const int yPosition) : Piece(color, xPosition, yPosition)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}



std::vector<Move> Rook::generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const
{
    std::vector<Move> moves;

    std::string color = grid[col][row]->getColor();

    checkAdjacentMoves(row, col, -1, 0, moves, grid, color); // Check left
    checkAdjacentMoves(row, col, 1, 0, moves, grid, color);  // Check right
    checkAdjacentMoves(row, col, 0, 1, moves, grid, color);  // Check above
    checkAdjacentMoves(row, col, 0, -1, moves, grid, color); // Check below

    return moves;
}

std::string Rook::getType() const
{
    return "Rook";
}

// Checks all rook moves
