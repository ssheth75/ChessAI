#ifndef PIECE_HPP
#define PIECE_HPP

#include "util.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Board;

class Piece;

struct Move
{
    Piece *piece;
    int endCol;
    int endRow;
    MoveType moveType;

    Move(Piece *piece, int endCol, int endRow, MoveType moveType) : piece(piece), endCol(endCol), endRow(endRow), moveType(moveType) {}
};

class Piece
{
public:
    Piece(Player color, const int col, const int row, const std::string name); // Constructor

    virtual Piece *clone() const = 0; // Pure virtual function for cloning

    virtual ~Piece();

    virtual std::vector<Move> generateMoves(int row, int col, const Board &board) const = 0;

    virtual std::string getType() const = 0; // Pure virtual function

    virtual int getVal() const = 0; // Pure virtual function

    virtual void draw(sf::RenderWindow &window, int x, int y, int squareSize);

    virtual bool hasMoved() const { return false; } // Default implementation for other pieces

    virtual void setMoved(bool moved) {}

    int m_col;
    int m_row;
    std::string m_name;
    const Player m_color;

protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

#endif
