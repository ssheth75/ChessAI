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
   


    PieceType showPawnPromotionMenu(Player Color);
    void draw(); // Draw the board and pieces
    std::vector<Move> generateAllMoves(Player color);

    // contains mappings of the piece name and its valid moves it can make for the current turn
    std::unordered_map<std::string, std::vector<Move>> m_validActiveMoves;
   


private:
    sf::RenderWindow m_window; // The game window
    Board m_board;             // The chessboard
    Player m_turn;
};

#endif
