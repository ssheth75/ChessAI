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
    Piece(Player color, const int col, const int row, const std::string name); // Constructor

    virtual Piece *clone() const = 0; // Pure virtual function for cloning

    virtual ~Piece();

    virtual std::vector<Move> generateMoves(int row, int col, const Board &board) const = 0;

    virtual std::string getType() const = 0; // Pure virtual function

    virtual void draw(sf::RenderWindow &window, int x, int y, int squareSize);

    Player getColor();

    int col;
    int row;
    std::string name;

protected:
    Player color;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
