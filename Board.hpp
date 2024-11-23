#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Piece.hpp"
#include "util.hpp"

struct KingPosition
{
    int x; // col
    int y; // row

    KingPosition(int x, int y) : x(x), y(y) {} // Constructor
};

struct MoveState
{
    Piece *movedPiece;    // The piece being moved
    int oldX, oldY;       // Original position of the piece
    Piece *capturedPiece; // Piece at the destination (if any)
};

class Board
{
public:
    Board();
    void draw(sf::RenderWindow &window);      // Draw the board and pieces
    void handleClick(int mouseX, int mouseY); // Handle mouse clicks
    void makeMove(Piece *piece, Move move);   // Make a move and update the board
    Piece *getPieceAt(int x, int y) const;    // Get the piece at a specific position
    void removePiece(const int row, const int col);

    bool movesHighlighted = false;
    std::vector<Move> highlightedMoves;     // Valid moves for the selected piece
    std::vector<std::vector<Piece *>> grid; // 2D grid of piece pointers

    void checkStarMoves(int startRow, int startCol, int rowStep, int colStep,
                        std::vector<Move> &moves, std::string &color) const;

    // bool inCheck(KingPosition king, std::string kingColor);

    std::string check = "Neither";

    KingPosition getKingPosition(const std::string color);

    MoveState move(Piece *piece, Move move);
    void undo(const MoveState &state);

    std::vector<Move> validatedMoves(std::vector<Move> potentialMoves, Piece *piece);
    bool inCheck(const std::string &kingColor);
    bool pieceUnderAttack(std::string color);

    KingPosition whiteKing;
    KingPosition blackKing;

    std::unordered_map<std::string, Piece *> whitePieces;
    std::unordered_map<std::string, Piece *> blackPieces;

private:
    sf::Texture pieceTextures[12]; // Textures for pieces
    sf::Sprite pieceSprites[12];   // Sprites for pieces

    void setupBoard(); // Initialize the board with pieces
};

#endif
