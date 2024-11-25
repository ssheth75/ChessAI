#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Piece.hpp"
#include "util.hpp"

struct KingPosition
{
    int col; // col
    int row; // row

    KingPosition(int col, int row) : col(col), row(row) {} // Constructor
};

struct MoveState
{
    bool isKing;
    Piece *movedPiece;    // The piece being moved
    int oldCol, oldRow;   // Original position of the piece
    Piece *capturedPiece; // Piece at the destination (if any)
};

struct Position
{
    int col; // col
    int row; // row

    Position(int col, int row) : col(col), row(row) {} // Constructor
};

class Board
{
public:
    // Constructor
    Board();

    // Public Member Functions
    void makeMove(Move move, const PieceType userSelection = PieceType::NONE); // Make a move and update the board
    void checkStarMoves(int startRow, int startCol, int rowStep, int colStep,
                        std::vector<Move> &moves, Player color) const; // Check specific moves
    std::vector<Move> validatedMoves(std::vector<Move> potentialMoves);
    void draw(sf::RenderWindow &window); // Draw the board and pieces

    bool squareUnderAttack(int col, int row, Player color) const; // Check if a piece is under attack. takes in friendly color
    Move rookCastleMove(Move move);

    // Public Member Variables
    bool m_movesHighlighted = false; // Tracks if moves are highlighted
    std::vector<Move> m_validMoves;  // Valid moves for the selected piece
    std::vector<std::vector<Piece *>> m_grid;
    std::unordered_map<std::string, Piece *> m_whitePieces; // White pieces map
    std::unordered_map<std::string, Piece *> m_blackPieces; // 2D grid of piece pointers
    int numPromoted = 0;                                    // used to keep track of the number of pieces that have been promoted

    // Commented function for potential future use
    // bool inCheck(KingPosition king, std::string kingColor);

private:
    // Private Member Variables
    sf::Texture m_pieceTextures[12]; // Textures for pieces
    sf::Sprite m_pieceSprites[12];   // Sprites for pieces
    // Black pieces map
    KingPosition m_whiteKing; // Position of the white king
    KingPosition m_blackKing; // Position of the black king

    // Private Member Functions
    void setupBoard();                                // Initialize the board with pieces
    KingPosition getKingPosition(Player color) const; // Get king's position by color
    bool inCheck(Player Color);                       // Check if a king is in check
    MoveState move(Move move);                        // Execute a move
    void undo(const MoveState &state);                // Undo a move
    void updateKingPosition(Piece *king, int col, int row);

    void handleClick(int mouseX, int mouseY); // Handle mouse clicks
};

#endif
