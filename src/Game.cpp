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
    this->draw(); // Draw the initial board
    m_window.display();

    sf::Event event;

    m_turn = Player::WHITE;

    auto allMoves = generateAllMoves(m_turn);
    m_board.validatedMoves(allMoves, this->m_validActiveMoves);

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
                handleClick(x, y, m_turn);

                // Render after processing the event
                m_window.clear(sf::Color::White);
                this->draw(); // Draw the board with pieces
                m_window.display();
            }
        }
    }
}

void Game::handleClick(const int x, const int y, Player &turn)
{
    int row = x / 100;
    int col = y / 100;

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;

    Piece *piece = m_board.m_grid[col][row];

    if (piece && piece->m_color == turn)
    {
        // highlignt the valid moves for the piece that was clicked
        m_board.m_highlightedMoves = m_validActiveMoves[piece->m_name];
        m_board.m_movesHighlighted = true;
    }
    else if (m_board.m_movesHighlighted && m_board.squareIsHighlighted(col, row)) // if opponent piece or null piece
    {
        for (const Move &validMove : m_board.m_highlightedMoves)
        {
            if (validMove.endCol == col && validMove.endRow == row)
            {
                // Make the move
                if (validMove.moveType == MoveType::PROMOTION)
                {
                    PieceType userSelection = showPawnPromotionMenu(validMove.piece->m_color);
                    m_board.makeMove(validMove, userSelection);
                }
                else
                {
                    m_board.makeMove(validMove);
                }

                // switch the turn
                turn = (turn == Player::BLACK ? Player::WHITE : Player::BLACK);
                m_board.m_highlightedMoves.clear();
                m_board.m_movesHighlighted = false;
                m_validActiveMoves.clear();
                auto allMoves = generateAllMoves(m_turn);
                m_board.validatedMoves(allMoves, this->m_validActiveMoves);
            }
        }
    }
    else
    {

        m_board.m_highlightedMoves.clear();
        m_board.m_movesHighlighted = false;
    }
    return;
}

std::vector<Move> Game::generateAllMoves(Player color)
{
    std::vector<Move> allMoves;
    // Iterate through the board grid
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = m_board.m_grid[col][row]; // Access the piece at the current position

            // If there's a piece and it matches the specified color
            if (piece != nullptr && piece->m_color == color)
            {
                // Generate moves for this piece
                std::vector<Move> pieceMoves = piece->generateMoves(col, row, m_board);

                // Append moves to the overall list
                allMoves.insert(allMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    return allMoves;
}

// Function to show the pawn promotion menu
PieceType Game::showPawnPromotionMenu(Player color)
{
    // Create a semi-transparent background
    sf::RectangleShape background(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 150));

    // Menu options
    const int menuWidth = 400;
    const int menuHeight = 100;
    const int optionSpacing = 20;

    sf::RectangleShape menu(sf::Vector2f(menuWidth, menuHeight));
    menu.setFillColor(sf::Color(200, 200, 200));
    menu.setPosition((m_window.getSize().x - menuWidth) / 2, (m_window.getSize().y - menuHeight) / 2);

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
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }

            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

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
        m_window.clear();
        m_window.draw(background);
        m_window.draw(menu);
        m_window.draw(queenSprite);
        m_window.draw(rookSprite);
        m_window.draw(bishopSprite);
        m_window.draw(knightSprite);
        m_window.display();
    }

    return userSelection;
}

void Game::draw()
{
    const int squareSize = 100;

    // Draw the chessboard m_grid
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(235, 236, 208, 255) : sf::Color(119, 149, 86, 255));
            m_window.draw(square);
        }
    }

    // Highlight valid moves
    sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
    highlight.setFillColor(sf::Color(0, 255, 0, 100)); // Semi-transparent green
    for (const Move &validMove : m_board.m_highlightedMoves)
    {
        highlight.setPosition(validMove.endRow * squareSize, validMove.endCol * squareSize);
        m_window.draw(highlight);
    }

    // Draw pieces
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = m_board.m_grid[row][col];
            if (piece)
            {
                piece->draw(m_window, col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}
