#include "Board.hpp"
#include <iostream>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"

Board::Board() {
    setupBoard();
}

void Board::setupBoard() {
    // Initialize the grid with nullptr (empty squares)
    grid = std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr));

    // Place black pieces
    grid[0][0] = new Rook("black");
    grid[0][1] = new Knight("black");
    grid[0][2] = new Bishop("black");
    grid[0][3] = new Queen("black");
    grid[0][4] = new King("black");
    grid[0][5] = new Bishop("black");
    grid[0][6] = new Knight("black");
    grid[0][7] = new Rook("black");

    for (int col = 0; col < 8; ++col) {
        grid[1][col] = new Pawn("black");
        grid[6][col] = new Pawn("white");
    }

    // Place white pieces
    grid[7][0] = new Rook("white");
    grid[7][1] = new Knight("white");
    grid[7][2] = new Bishop("white");
    grid[7][3] = new Queen("white");
    grid[7][4] = new King("white");
    grid[7][5] = new Bishop("white");
    grid[7][6] = new Knight("white");
    grid[7][7] = new Rook("white");
}

// void Board::handleClick(int mouseX, int mouseY) {
//     int col = mouseX / 100;  // Convert mouse position to grid coordinates
//     int row = mouseY / 100;

//     // Ensure the click is within bounds
//     if (row < 0 || row >= 8 || col < 0 || col >= 8) return;

//     // Get the clicked piece
//     Piece* piece = getPieceAt(col, row);
//     if (piece) {
//         std::vector<Move> possibleMoves = piece->generateMoves(row, col, grid);

//         // Highlight possible moves or pass them to the UI
//         for (const Move& move : possibleMoves) {
//             std::cout << "Possible move: (" << move.x << ", " << move.y << ")\n";
//         }
//     }
// }

void Board::draw(sf::RenderWindow &window) {
    const int squareSize = 100;

    // Draw the chessboard grid
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Create and position a square for the chessboard
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);

            // Alternate colors for the squares
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(235, 236, 208, 255) : sf::Color(119, 149, 86, 255));
            window.draw(square);

            // Draw the piece if one exists on this square
            Piece* piece = grid[row][col];
            if (piece != nullptr) {
                piece->draw(window, col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}

void Board::removePiece(const int row, const int col){
    delete grid[row][col];
    grid[row][col] = nullptr;
    
}



Piece* Board::getPieceAt(int x, int y) const{
    // Only access if piece present
    if (grid[x][y]){
        std:: cout << "piece type: " << grid[x][y]->getType() << std::endl;
        return grid[x][y];
    }

    return nullptr;
}
