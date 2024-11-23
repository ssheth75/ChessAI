#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "King.hpp"
#include "Board.hpp"
#include <iostream>

King::King(const std::string &color, const int xPosition, const int yPosition, const std::string name) : Piece(color, xPosition, yPosition, name)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}

std::vector<Move> King::generateMoves(int col, int row, const Board &board) const
{
    std::vector<Move> potentialMoves;
    std::string color = board.grid[col][row]->getColor();

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
            Piece *target = board.grid[newCol][newRow];
            if (target == nullptr || target->getColor() != color) // Empty or opponent's piece
            {
                potentialMoves.push_back({newCol, newRow});
            }
        }
    }

    // Add castling

    return potentialMoves;
}

std::string King::getType() const
{
    return "King";
}
