#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "util.hpp"
#include "Piece.hpp"

class Board
{
public:
    Board();
    void draw(sf::RenderWindow &window);      // Draw the board and pieces
    void handleClick(int mouseX, int mouseY); // Handle mouse clicks
    void makeMove(Piece *piece, Move move);   // Make a move and update the board
    Piece *getPieceAt(int x, int y) const;    // Get the piece at a specific position
    void removePiece(const int row, const int col);

private:
    std::vector<std::vector<Piece *>> grid; // 2D grid of piece pointers
    sf::Texture pieceTextures[12];          // Textures for pieces
    sf::Sprite pieceSprites[12];            // Sprites for pieces

    void setupBoard(); // Initialize the board with pieces
};

#endif
