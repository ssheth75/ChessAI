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
    uint16_t row = y / 100;
    uint16_t col = x / 100;


    std::cout << "row: " << row << " col: " << col << " " << std::endl;

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;

    // Get the clicked piece
    Piece *piece = board.getPieceAt(row, col);
    if (piece)
    {
        board.removePiece(row, col);
        // std::vector<Move> possibleMoves = piece->generateMoves(row, col, grid);

        // // Highlight possible moves or pass them to the UI
        // for (const Move& move : possibleMoves) {
        //     std::cout << "Possible move: (" << move.x << ", " << move.y << ")\n";
        // }
    }

    turn = !turn;
}
