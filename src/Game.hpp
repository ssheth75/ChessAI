#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();     // Constructor to initialize the game
    void run(); // Main game loop

    void handleClick(const int x, const int y, Player &turn);

    PieceType showPawnPromotionMenu(sf::RenderWindow &window, Player Color);


private:
    sf::RenderWindow m_window;            // The game window
    Board m_board;                        // The chessboard
    Piece *m_selectedPiece = nullptr;     // Currently selected piece
    Player turn;
};

#endif
