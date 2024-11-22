#include "Board.hpp"
#include <iostream>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"


Board::Board()
{
    setupBoard();
}

void Board::setupBoard()
{
    // Initialize the grid with nullptr (empty squares)
    grid = std::vector<std::vector<Piece *>>(8, std::vector<Piece *>(8, nullptr));

    // Place black pieces
    grid[0][0] = new Rook("black", 0, 0);
    grid[0][1] = new Knight("black", 0, 1);
    grid[0][2] = new Bishop("black", 0, 2);
    grid[0][3] = new Queen("black", 0, 3);
    grid[0][4] = new King("black", 0, 4);
    grid[0][5] = new Bishop("black", 0, 5);
    grid[0][6] = new Knight("black", 0, 6);
    grid[0][7] = new Rook("black", 0, 7);

    for (int col = 0; col < 8; ++col)
    {
        grid[1][col] = new Pawn("black", 1, col);
        grid[6][col] = new Pawn("white", 6, col);
    }

    // Place white pieces
    grid[7][0] = new Rook("white", 7, 0);
    grid[7][1] = new Knight("white", 7, 1);
    grid[7][2] = new Bishop("white", 7, 2);
    grid[7][3] = new Queen("white", 7, 3);
    grid[7][4] = new King("white", 7, 4);
    grid[7][5] = new Bishop("white", 7, 5);
    grid[7][6] = new Knight("white", 7, 6);
    grid[7][7] = new Rook("white", 7, 7);
}

void Board::draw(sf::RenderWindow &window)
{
 const int squareSize = 100;

    // Draw the chessboard grid
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(235, 236, 208, 255) : sf::Color(119, 149, 86, 255));
            window.draw(square);
        }
    }

    // Highlight valid moves
    sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
    highlight.setFillColor(sf::Color(0, 255, 0, 100));  // Semi-transparent green
    for (const Move &move : highlightedMoves) {
        highlight.setPosition(move.y * squareSize, move.x * squareSize);
        window.draw(highlight);
    }

    // Draw pieces
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece *piece = grid[row][col];
            if (piece) {
                piece->draw(window, col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}

void Board::removePiece(const int col, const int row)
{
    delete grid[col][row];
    grid[col][row] = nullptr;
}

// Implement
bool Board::inCheck(const bool &turn)
{
    return false;
}

// input: move = [col,row]
Piece *Board::getPieceAt(int x, int y) const
{
    // Only access if piece present
    if (grid[x][y])
    {
        std::cout << "piece type: " << grid[x][y]->getType() << std::endl;
        return grid[x][y];
    }

    return nullptr;
}
// input: move = [col,row]
void Board::makeMove(Piece *piece, Move move) {
    // Capture logic: delete the opponent's piece if present
    if (grid[move.x][move.y] != nullptr && grid[move.x][move.y]->getColor() != piece->getColor()) {
        delete grid[move.x][move.y];  // Remove the captured piece
    }

    // Update the grid: move the piece
    grid[move.x][move.y] = piece;                        // Place the piece in the new position
    grid[piece->xPosition][piece->yPosition] = nullptr;  // Clear the old position

    // Update the piece's internal position
    piece->xPosition = move.x;
    piece->yPosition = move.y;
}
