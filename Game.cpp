#include "Game.hpp"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 800), "Chess AI"), board()
{
    // Initialize other game components if needed
}

void Game::run()
{
    // Initial render before entering the event loop
    window.clear(sf::Color::White);
    board.draw(window); // Draws the initial board
    window.display();
    bool turn = true; // white, black = false

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Handle other events
                int x = event.mouseButton.x; // X-coordinate of the mouse click
                int y = event.mouseButton.y; // Y-coordinate of the mouse click
                handleClick(x, y, turn);

                // Render after processing the event
                window.clear(sf::Color::White);
                board.draw(window); // Draws the board with pieces
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
        for (const Move &move : board.highlightedMoves)
        {
            if (move.x == col && move.y == row)
            {
                // Make the move
                board.makeMove(selectedPiece, move);

                // Clear the selected piece and highlighted moves
                selectedPiece = nullptr;
                board.highlightedMoves.clear();

                // Toggle the turn
                turn = !turn;

                return;
            }
        }

        // If not a valid move, deselect the piece
        selectedPiece = nullptr;
        board.highlightedMoves.clear();
    }

    // Get the piece at the clicked position
    Piece *piece = board.getPieceAt(col, row);

    // Select the piece if it matches the current turn
    if (piece && piece->getColor() == (turn ? "white" : "black"))
    {
        selectedPiece = piece;

        // Generate valid moves
        board.highlightedMoves = piece->generateMoves(row, col, board.grid);


        // Log the moves for debugging
        std::cout << "Valid moves for " << piece->getType() << " at (" << row << ", " << col << "):" << std::endl;
        for (const Move &move : board.highlightedMoves)
        {
            std::cout << "(" << move.x << ", " << move.y << ")" << std::endl;
        }
    }


}
