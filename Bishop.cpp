#include "Piece.hpp"
#include <vector>
#include "util.hpp"
#include "Bishop.hpp"
#include <iostream>

Bishop::Bishop(const std::string &color) : Piece(color)
{
    std::string textureFile = (color == "white") ? this->whiteGraphic : this->blackGraphic;

    if (!texture.loadFromFile(textureFile))
    {
        std::cout << "Error loading texture: " << textureFile << std::endl;
    }
    sprite.setTexture(texture); // Set the loaded texture to the sprite
}

std::vector<Move> Bishop::generateMoves(uint32_t row, uint32_t col, const std::vector<std::vector<Piece *>> &grid) const
{
    return {};
}

std::string Bishop::getType() const
{
    return "Bishop";
}
