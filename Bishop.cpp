#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Bishop.hpp"
#include <iostream>

Bishop::Bishop(const std::string &color, const int xPosition, const int yPosition) : Piece(color, xPosition, yPosition)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}

std::vector<Move> Bishop::generateMoves(int row, int col, const std::vector<std::vector<Piece *>> &grid) const
{
    return {};
}

std::string Bishop::getType() const
{
    return "Bishop";
}
