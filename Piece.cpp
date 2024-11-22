#include <string>
#include <vector>
#include "util.hpp"
#include "Piece.hpp"
#include <iostream>


Piece::Piece(const std::string& color, int xPosition, int yPosition) : color(color), xPosition(xPosition), yPosition(yPosition) {}

Piece::~Piece() {}

void Piece::draw(sf::RenderWindow& window, int x, int y, int squareSize) {
    if (!sprite.getTexture()) {
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

std::string Piece::getColor(){
    return color;
}
