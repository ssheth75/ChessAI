#include "Game.hpp"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 800), "Chess AI"), board()
{
    // Initialize other game components if needed
}

void Game::run()
{
    // Initial render
    window.clear(sf::Color::White);
    board.draw(window); // Draw the initial board
    window.display();

    bool turn = true; // true = white's turn, false = black's turn

    sf::Event event;

    // Main event-driven loop
    while (window.isOpen())
    {
        // Wait for an event
        if (window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Handle click events
                int x = event.mouseButton.x; // X-coordinate of the mouse click
                int y = event.mouseButton.y; // Y-coordinate of the mouse click
                handleClick(x, y, turn);

                // Render after processing the event
                window.clear(sf::Color::White);
                board.draw(window); // Draw the board with pieces
                window.display();
            }
        }
    }
}


void Game::handleClick(const int x, const int y, bool &turn)
{
    // Update game logic based on the event
    // For example, move pieces, handle clicks, etc.
    std::cout << "x: " << x << " y: " << y << " " << std::endl;
    uint16_t row = x / 100;
    uint16_t col = y / 100;

    std::cout << "row: " << row << " col: " << col << " " << std::endl;

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;

    if (selectedPiece)
    {
        // Check if the clicked square is a valid move
        for (const Move &move : board.m_validMoves)
        {
            if (move.col == col && move.row == row)
            {
                // Make the move
                board.makeMove(selectedPiece, move);

                // Clear the selected piece and highlighted moves
                selectedPiece = nullptr;
                board.m_validMoves.clear();

                // Toggle the turn
                turn = !turn;

                return;
            }
        }

        // If not a valid move, deselect the piece
        selectedPiece = nullptr;
        board.m_validMoves.clear();
    }

    // Get the piece at the clicked position
    Piece *piece = board.getPieceAt(col, row);

    // Select the piece if it matches the current turn
    if (piece && piece->getColor() == (turn ? Player::WHITE : Player::BLACK))
    {
        selectedPiece = piece;
        // Generate valid moves
        auto allMoves = piece->generateMoves(col, row, board);
        board.m_validMoves = board.validatedMoves(allMoves, piece);

        // Log the moves for debugging
        std::cout << "Valid moves for " << piece->getType() << " at (" << row << ", " << col << "):" << std::endl;
        for (const Move &move : board.m_validMoves)
        {
            std::cout << "(" << move.col << ", " << move.row << ")" << std::endl;
        }
    }
}
