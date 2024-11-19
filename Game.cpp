#include "Game.hpp"

Game::Game() 
    : window(sf::VideoMode(800, 800), "Chess AI"), board() {
    // Initialize other game components if needed

    
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Game logic here (e.g., handle moves, check for game over)

        // Render the board and pieces
        window.clear(sf::Color::White);
        board.draw(window);  // Draws the board with pieces
        window.display();
    }
}
