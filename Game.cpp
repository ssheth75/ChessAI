#include "Game.hpp"
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode(800, 800), "Chess AI"), m_board()
{
    // Initialize other game components if needed
}

void Game::run()
{
    // Initial render
    m_window.clear(sf::Color::White);
    m_board.draw(m_window); // Draw the initial board
    m_window.display();

    sf::Event event;

    turn = Player::WHITE;

    // Main event-driven loop
    while (m_window.isOpen())
    {
        // Wait for an event
        if (m_window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Handle click events
                int x = event.mouseButton.x; // X-coordinate of the mouse click
                int y = event.mouseButton.y; // Y-coordinate of the mouse click
                handleClick(x, y, turn);

                // Render after processing the event
                m_window.clear(sf::Color::White);
                m_board.draw(m_window); // Draw the board with pieces
                m_window.display();
            }
        }
    }
}

void Game::handleClick(const int x, const int y, Player &turn)
{
    // Update game logic based on the event
    // For example, move pieces, handle clicks, etc.
    std::cout << "x: " << x << " y: " << y << " " << std::endl;
    uint16_t row = x / 100;
    uint16_t col = y / 100;

    std::cout << "row: " << row << " col: " << col << " " << std::endl;

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;

    if (m_selectedPiece)
    {
        // Check if the clicked square is a valid move
        for (const Move &validMove : m_board.m_validMoves)
        {
            if (validMove.endCol == col && validMove.endRow == row)
            {
                // Make the move

                if (validMove.moveType == MoveType::PROMOTION)
                {
                    PieceType userSelection = showPawnPromotionMenu(m_window, m_selectedPiece->m_color);
                    m_board.makeMove(validMove, userSelection);
                }
                else
                {
                    m_board.makeMove(validMove);
                }

                // Clear the selected piece and highlighted moves
                m_selectedPiece = nullptr;
                m_board.m_validMoves.clear();

                // switch the turn
                turn = (turn == Player::BLACK ? Player::WHITE : Player::BLACK);

                return;
            }
        }

        // If not a valid move, deselect the piece
        m_selectedPiece = nullptr;
        m_board.m_validMoves.clear();
    }

    // Get the piece at the clicked position
    Piece *piece = m_board.m_grid[col][row];

    // Select the piece if it matches the current turn
    if (piece && piece->m_color == (turn == Player::WHITE ? Player::WHITE : Player::BLACK))
    {
        m_selectedPiece = piece;
        // Generate valid moves
        auto allMoves = piece->generateMoves(col, row, m_board);
        m_board.m_validMoves = m_board.validatedMoves(allMoves);

        // Log the moves for debugging
        //std::cout << "Valid moves for " << piece->getType() << " at (" << row << ", " << col << "):" << std::endl;
        for (const Move &move : m_board.m_validMoves)
        {
            std::cout << "(" << move.endCol << ", " << move.endRow << ")" << std::endl;
        }
    }
}

// Function to show the pawn promotion menu
PieceType Game::showPawnPromotionMenu(sf::RenderWindow &window, Player color)
{
    // Create a semi-transparent background
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 150));

    // Menu options
    const int menuWidth = 400;
    const int menuHeight = 100;
    const int optionSpacing = 20;

    sf::RectangleShape menu(sf::Vector2f(menuWidth, menuHeight));
    menu.setFillColor(sf::Color(200, 200, 200));
    menu.setPosition((window.getSize().x - menuWidth) / 2, (window.getSize().y - menuHeight) / 2);

    // Load textures for the pieces (ensure these paths are correct)
    sf::Texture queenTexture, rookTexture, bishopTexture, knightTexture;

    queenTexture.loadFromFile((color == Player::BLACK ? "assets/bq.png" : "assets/wq.png"));
    rookTexture.loadFromFile((color == Player::BLACK ? "assets/br.png" : "assets/wr.png"));
    bishopTexture.loadFromFile((color == Player::BLACK ? "assets/bb.png" : "assets/wb.png"));
    knightTexture.loadFromFile((color == Player::BLACK ? "assets/bn.png" : "assets/wn.png"));

    // Create sprites for the options
    sf::Sprite queenSprite(queenTexture);
    sf::Sprite rookSprite(rookTexture);
    sf::Sprite bishopSprite(bishopTexture);
    sf::Sprite knightSprite(knightTexture);

    // Scale and position the sprites
    const float scale = 0.5f;
    queenSprite.setScale(scale, scale);
    rookSprite.setScale(scale, scale);
    bishopSprite.setScale(scale, scale);
    knightSprite.setScale(scale, scale);

    queenSprite.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 20);
    rookSprite.setPosition(queenSprite.getPosition().x + 100, menu.getPosition().y + 20);
    bishopSprite.setPosition(rookSprite.getPosition().x + 100, menu.getPosition().y + 20);
    knightSprite.setPosition(bishopSprite.getPosition().x + 100, menu.getPosition().y + 20);

    PieceType userSelection;

    // Event loop for menu
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (queenSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    userSelection = PieceType::QUEEN;
                }
                else if (rookSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    userSelection = PieceType::ROOK;
                }
                else if (bishopSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    userSelection = PieceType::BISHOP;
                }
                else if (knightSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    userSelection = PieceType::KNIGHT;
                }

                if (userSelection != PieceType::NONE)
                {
                    return userSelection; // Exit the function with the user's choice
                }
            }
        }

        // Render the menu
        window.clear();
        window.draw(background);
        window.draw(menu);
        window.draw(queenSprite);
        window.draw(rookSprite);
        window.draw(bishopSprite);
        window.draw(knightSprite);
        window.display();
    }

    return userSelection;
}
