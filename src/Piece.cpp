#include <string>
#include <vector>
#include "Piece.hpp"
#include <iostream>
#include "util.hpp"

Piece::Piece(Player color, const int col, const int row, const std::string name) : m_color(color), m_col(col), m_row(row), m_name(name) {}


Piece::~Piece() {}

void Piece::draw(sf::RenderWindow &window, int x, int y, int squareSize)
{
    if (!m_sprite.getTexture())
    {
        std::cout << "Sprite has no texture set!\n";
        return;
    }

    // Set the sprite's position
    m_sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

    // Scale the sprite to fit the square size
    float scaleX = static_cast<float>(squareSize) / m_sprite.getTexture()->getSize().x;
    float scaleY = static_cast<float>(squareSize) / m_sprite.getTexture()->getSize().y;
    m_sprite.setScale(scaleX, scaleY);

    // Draw the sprite
    window.draw(m_sprite);
}
