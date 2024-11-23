#include <string>
#include <vector>
#include "Piece.hpp"
#include <iostream>
#include "util.hpp"

Piece::Piece(const std::string &color, const int xPosition, const int yPosition, const std::string name) : color(color), xPosition(xPosition), yPosition(yPosition), name(name) {}


Piece::~Piece() {}

void Piece::draw(sf::RenderWindow &window, int x, int y, int squareSize)
{
    if (!sprite.getTexture())
    {
        std::cout << "Sprite has no texture set!\n";
        return;
    }

    // Set the sprite's position
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

    // Scale the sprite to fit the square size
    float scaleX = static_cast<float>(squareSize) / sprite.getTexture()->getSize().x;
    float scaleY = static_cast<float>(squareSize) / sprite.getTexture()->getSize().y;
    sprite.setScale(scaleX, scaleY);

    // Draw the sprite
    window.draw(sprite);
}

std::string Piece::getColor()
{
    return color;
}
