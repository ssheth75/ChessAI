#include "Board.hpp"
#include <iostream>
#include "Piece.hpp"

Board::Board() {
    loadTextures();
    setupBoard();
}

void Board::loadTextures() {
    const std::string pieces[12] = {
        "assets/wp.png", "assets/wr.png", "assets/wn.png",
        "assets/wb.png", "assets/wq.png", "assets/wk.png",
        "assets/bp.png", "assets/br.png", "assets/bn.png",
        "assets/bb.png", "assets/bq.png", "assets/bk.png"
    };

    for (int i = 0; i < 12; ++i) {
        if (!pieceTextures[i].loadFromFile(pieces[i])) {
            std::cerr << "Error loading texture: " << pieces[i] << std::endl;
        }
        pieceSprites[i].setTexture(pieceTextures[i]);

        float scaleFactor = 100.0f / pieceTextures[i].getSize().x;
        pieceSprites[i].setScale(scaleFactor, scaleFactor);
    }
}

void Board::setupBoard() {
    // Define the initial state of the board using a 2D grid
    // 0 = empty, 1-12 = different piece types
    grid = {
        {8, 10, 9, 11, 12, 9, 10, 8}, // Black major pieces
        {7, 7, 7, 7, 7, 7, 7, 7},     // Black pawns
        {0, 0, 0, 0, 0, 0, 0, 0},     // Empty rows
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},     // White pawns
        {2, 4, 3, 5, 6, 3, 4, 2}      // White major pieces
    };
}

void Board::draw(sf::RenderWindow &window) {
    const int squareSize = 100;

    // Draw the chessboard grid
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(235, 236, 208, 255) : sf::Color(119, 149, 86, 255));
            window.draw(square);

            // Draw pieces
            if (grid[row][col] != 0) {
                int pieceIndex = grid[row][col] - 1;
                pieceSprites[pieceIndex].setPosition(col * squareSize, row * squareSize);
                window.draw(pieceSprites[pieceIndex]);
            }
        }
    }
}


void makeMove(Piece* piece, Move move){

}
