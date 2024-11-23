#include "util.hpp"
#include "Piece.hpp"
#include <vector>
#include "Bishop.hpp"
#include "Board.hpp"
#include <iostream>

Bishop::Bishop(const std::string &color, const int xPosition, const int yPosition, const std::string name) : Piece(color, xPosition, yPosition, name)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}

std::vector<Move> Bishop::generateMoves(int col, int row, const Board &board) const
{
    std::string color = board.grid[col][row]->getColor();

    // GENERATE ALL MOVES THAT CAUSE OR ARE A NON SELF-CHECK STATE

    // Check diagonals for potential moves
    std::vector<Move> potentialMoves;
    board.checkStarMoves(row, col, -1, 1, potentialMoves, color);
    board.checkStarMoves(row, col, 1, -1, potentialMoves, color);
    board.checkStarMoves(row, col, 1, 1, potentialMoves, color);
    board.checkStarMoves(row, col, -1, -1, potentialMoves, color);


    return potentialMoves;
}

std::string Bishop::getType() const
{
    return "Bishop";
}
