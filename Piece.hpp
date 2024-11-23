#ifndef PIECE_HPP
#define PIECE_HPP

#include "util.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Board;

class Piece
{
public:
    Piece(const std::string &color, const int xPostion, const int yPosition, const std::string name); // Constructor

    virtual Piece *clone() const = 0; // Pure virtual function for cloning

    virtual ~Piece();

    virtual std::vector<Move> generateMoves(int row, int col, const Board &board) const = 0;

    virtual std::string getType() const = 0; // Pure virtual function

    virtual void draw(sf::RenderWindow &window, int x, int y, int squareSize);

    std::string getColor();

    int xPosition;
    int yPosition;
    std::string name;

protected:
    std::string color;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
