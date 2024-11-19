#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();            // Constructor to initialize the game
    void run();        // Main game loop

private:
    sf::RenderWindow window;  // The game window
    Board board;              // The chessboard
};

#endif
