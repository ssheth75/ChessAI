#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "util.cpp"
#include "Piece.hpp"

class Board {
public:
    Board();  // Constructor to load resources and set up the board
    void draw(sf::RenderWindow &window);  // Draw the board and pieces

    void makeMove(Piece piece, Move move);

private:
    sf::Texture pieceTextures[12];  // Textures for all 12 chess piece types
    sf::Sprite pieceSprites[12];    // Sprites for rendering the pieces
    std::vector<std::vector<int>> grid;  // 2D grid for the board state

    void loadTextures();   // Load PNG images for pieces
    void setupBoard();     // Place pieces in initial positions
};

#endif
