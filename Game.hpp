#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();     // Constructor to initialize the game
    void run(); // Main game loop

    void handleClick(const int x, const int y, bool &turn);

private:
    sf::RenderWindow window;            // The game window
    Board board;                        // The chessboard
    Piece *selectedPiece = nullptr;     // Currently selected piece
};

#endif
