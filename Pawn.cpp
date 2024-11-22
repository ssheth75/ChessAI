#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(const std::string &color, const int xPosition, const int yPosition) : Piece(color, xPosition, yPosition)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}


// col is first and row is second. col = x; row = y; board uses this and is the same as cartesian
std::vector<Move> Pawn::generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const
{
    std::vector<Move> moves;

    // Direction: +1 for black, -1 for white
    int direction = (color == "white") ? -1 : 1;

    // Forward Move
    if (col + direction >= 0 && col + direction < 8 && grid[col + direction][row] == nullptr)
    {
        moves.push_back({col + direction, row}); // Single forward move

        // Double Forward Move (only from starting position)
        if ((color == "white" && col == 6) || (color == "black" && col == 1))
        {
            if (grid[col + 2 * direction][row] == nullptr)
            {
                moves.push_back({col + (2 * direction), row});
                std::cout<< col + (2 * direction) << std::endl;
                std::cout<< row <<std::endl;
            }
        }
    }

    // Capture Left
    if (row - 1 >= 0 && col + direction >= 0 && col + direction < 8)
    {
        Piece *target = grid[col + direction][row - 1];
        if (target != nullptr && target->getColor() != color)
        {

            moves.push_back({col + direction, row - 1}); // Diagonal capture left
        }
    }

    // Capture Right
    if (row + 1 < 8 && col + direction >= 0 && col + direction < 8)
    {
        Piece *target = grid[col + direction][row + 1];
        if (target != nullptr && target->getColor() != color)
        {
            moves.push_back({col + direction, row + 1}); // Diagonal capture right
        }
    }


    // Implement en passant later

    return moves;



}

std::string Pawn::getType() const
{
    return "Pawn";
}
