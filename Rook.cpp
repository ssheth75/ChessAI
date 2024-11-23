#include "util.hpp"
#include "Piece.hpp"
#include <vector>
#include "Rook.hpp"
#include "Board.hpp"
#include <iostream>

Rook::Rook(const std::string &color, const int xPosition, const int yPosition, const std::string name) : Piece(color, xPosition, yPosition, name)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}

std::vector<Move> Rook::generateMoves(int col, int row, const Board &board) const
{

    std::vector<Move> potentialMoves;
    std::string color = board.grid[col][row]->getColor();

    // Check left, right, up, down
    board.checkStarMoves(row, col, -1, 0, potentialMoves, color); // Check left
    board.checkStarMoves(row, col, 1, 0, potentialMoves, color);  // Check right
    board.checkStarMoves(row, col, 0, 1, potentialMoves, color);  // Check above
    board.checkStarMoves(row, col, 0, -1, potentialMoves, color); // Check below

    // add castling

    return potentialMoves;
}

std::string Rook::getType() const
{
    return "Rook";
}

// Checks all rook moves
