#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Knight.hpp"
#include <iostream>
#include "Board.hpp"

Knight::Knight(const std::string &color, const int xPosition, const int yPosition, const std::string name) : Piece(color, xPosition, yPosition, name)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}

std::vector<Move> Knight::generateMoves(int col, int row, const Board &board) const
{
    std::vector<Move> potentialMoves;
    std::string color = board.grid[col][row]->getColor();

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
            Piece *target = board.grid[newCol][newRow];
            if (target == nullptr || target->getColor() != color) // Empty or opponent's piece
            {
                potentialMoves.push_back({newCol, newRow});
            }
        }
    }

    return potentialMoves;
}

std::string Knight::getType() const
{
    return "Knight";
}
