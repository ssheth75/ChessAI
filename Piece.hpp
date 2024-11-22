#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "util.hpp"

class Piece {
public:
    Piece(const std::string& color, int xPostion, int yPosition);  // Constructor
    
    virtual ~Piece();

    virtual std::vector<Move>generateMoves(int row, int col, const std::vector<std::vector<Piece*>> &grid) const = 0;

    virtual std::string getType() const = 0;  // Pure virtual function

    virtual void draw(sf::RenderWindow& window, int x, int y, int squareSize);

    std::string getColor();

    int xPosition;
    int yPosition;


protected:
    std::string color;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
