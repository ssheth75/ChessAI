#include "Board.hpp"
#include <iostream>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"

Board::Board() : whiteKing(7, 4), blackKing(0, 4)
{
    setupBoard();
}

void Board::setupBoard()
{
    // Initialize the grid with nullptr (empty squares)
    grid = std::vector<std::vector<Piece *>>(8, std::vector<Piece *>(8, nullptr));

    // Place black pieces
    grid[0][0] = new Rook("black", 0, 0, "br1");
    blackPieces["br1"] = grid[0][0];
    grid[0][1] = new Knight("black", 0, 1, "bn1");
    blackPieces["bn1"] = grid[0][1];
    grid[0][2] = new Bishop("black", 0, 2, "bb1");
    blackPieces["bb1"] = grid[0][2];
    grid[0][3] = new Queen("black", 0, 3, "bq");
    blackPieces["bq"] = grid[0][3];
    grid[0][4] = new King("black", 0, 4, "bk");
    blackPieces["bk"] = grid[0][4];
    grid[0][5] = new Bishop("black", 0, 5, "bb2");
    blackPieces["bb2"] = grid[0][5];
    grid[0][6] = new Knight("black", 0, 6, "bn2");
    blackPieces["bn2"] = grid[0][6];
    grid[0][7] = new Rook("black", 0, 7, "br2");
    blackPieces["br2"] = grid[0][7];

    for (int col = 0; col < 8; ++col)
    {
        grid[1][col] = new Pawn("black", 1, col, "bp" + std::to_string(col + 1));
        blackPieces["bp" + std::to_string(col + 1)] = grid[1][col];

        grid[6][col] = new Pawn("white", 6, col, "wp" + std::to_string(col + 1));
        whitePieces["wp" + std::to_string(col + 1)] = grid[6][col];
    }

    // Place white pieces
    grid[7][0] = new Rook("white", 7, 0, "wr1");
    whitePieces["wr1"] = grid[7][0];
    grid[7][1] = new Knight("white", 7, 1, "wn1");
    whitePieces["wn1"] = grid[7][1];
    grid[7][2] = new Bishop("white", 7, 2, "wb1");
    whitePieces["wb1"] = grid[7][2];
    grid[7][3] = new Queen("white", 7, 3, "wq");
    whitePieces["wq"] = grid[7][3];
    grid[7][4] = new King("white", 7, 4, "wk");
    whitePieces["wk"] = grid[7][4];
    grid[7][5] = new Bishop("white", 7, 5, "wb2");
    whitePieces["wb2"] = grid[7][5];
    grid[7][6] = new Knight("white", 7, 6, "wn2");
    whitePieces["wn2"] = grid[7][6];
    grid[7][7] = new Rook("white", 7, 7, "wr2");
    whitePieces["wr2"] = grid[7][7];
}

void Board::draw(sf::RenderWindow &window)
{
    const int squareSize = 100;

    // Draw the chessboard grid
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(235, 236, 208, 255) : sf::Color(119, 149, 86, 255));
            window.draw(square);
        }
    }

    // Highlight valid moves
    sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
    highlight.setFillColor(sf::Color(0, 255, 0, 100)); // Semi-transparent green
    for (const Move &move : highlightedMoves)
    {
        highlight.setPosition(move.y * squareSize, move.x * squareSize);
        window.draw(highlight);
    }

    // Draw pieces
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = grid[row][col];
            if (piece)
            {
                piece->draw(window, col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}

void Board::removePiece(const int col, const int row)
{
    delete grid[col][row];
    grid[col][row] = nullptr;
}

// input: move = [col,row]
Piece *Board::getPieceAt(int x, int y) const
{
    // Only access if piece present
    if (grid[x][y])
    {
        std::cout << "piece type: " << grid[x][y]->getType() << std::endl;
        return grid[x][y];
    }

    return nullptr;
}

// Used for Rook and Queen
void Board::checkStarMoves(int startRow, int startCol, int rowStep, int colStep,
                           std::vector<Move> &moves, std::string &color) const
{
    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow >= 0 && currentRow < 8 && currentCol >= 0 && currentCol < 8)
    {
        if (grid[currentCol][currentRow] == nullptr)
        {
            moves.push_back({currentCol, currentRow});
            currentRow += rowStep;
            currentCol += colStep;
        }
        else if (grid[currentCol][currentRow]->getColor() != color)
        {
            moves.push_back({currentCol, currentRow});
            break;
        }
        else
        {
            break;
        }
    }
}

std::string opponent(std::string color)
{
    return (color == "black") ? "white" : "black";
}



KingPosition Board::getKingPosition(const std::string color)
{
    return color == "black" ? this->blackKing : whiteKing;
}

// color is the color of the opponent king. We want to see if the move
// we just made put their king in check as that will influence their
// future possible moves.

bool Board::pieceUnderAttack(std::string color) {
    // Opponent pieces are stored in the opposite color's list
    std::unordered_map<std::string, Piece *> &opponentPieces = (color == "black" ? this->whitePieces : this->blackPieces);
    KingPosition king = getKingPosition(color);

    for (auto &piece : opponentPieces) {
        // Use `->` because `piece.second` is a pointer to a Piece
        std::vector<Move> moves = piece.second->generateMoves(piece.second->xPosition, piece.second->yPosition, *this);

        for (auto move : moves){
            if (move.x == king.x && move.y == king.y){
                return true;
            }
        }
    }

    return false;
}




bool Board::inCheck(const std::string &kingColor)
{
    // Determine the opponent's pieces based on the king's color
    return pieceUnderAttack(kingColor);
    
    return false; // The king is not in check
}

// Ensure that no move creates a self-checked state.
std::vector<Move> Board::validatedMoves(std::vector<Move> potentialMoves, Piece *piece)
{
    // Evaluate each move
    std::vector<Move> moves;

    for (const auto &move : potentialMoves)
    {

        auto undoState = this->move(piece, move);

        // Check if king is = in check
        if (!inCheck(piece->getColor()))
        {
            moves.push_back(move); // Valid move
        }

        this->undo(undoState);
    }

    return moves;
}



// input: move = [col,row]
void Board::makeMove(Piece *piece, Move move)
{
    // whenever a move is made the result cannot be a check on themself so reset check
    check = "neither";

    // Capture logic: delete the opponent's piece if present
    if (grid[move.x][move.y] != nullptr && grid[move.x][move.y]->getColor() != piece->getColor())
    {
        auto &pieces = (grid[move.x][move.y]->getColor() == "black") ? blackPieces : whitePieces;
        pieces.erase(grid[move.x][move.y]->name); // Erase from the appropriate map
        delete grid[move.x][move.y];              // Remove the captured piece
    }

    this->move(piece, move);

    // if we just moved a king piece then update KingPosition for that piece
    if (piece->getType() == "King")
    {
        if (piece->getColor() == "black")
        {
            blackKing.x = move.x;
            blackKing.y = move.y;
        }
        else if (piece->getColor() == "white")
        {
            whiteKing.x = move.x;
            whiteKing.y = move.y;
        }
    }

    // after making a move check if that put the opponent king in check.
    // do so by passing in the opponents king
    // KingPosition king = (piece->getColor() == "black" ? whiteKing : blackKing);
    // if (inCheck(king, opponent(piece->getColor()), this)) // 'this' is the board
    // {
    //     // if the king is in check that means that the kings color is in check
    //     check = opponent(piece->getColor());
    //     std::cout << opponent(piece->getColor()) << " is in check" << std::endl;

    //     // check for mate as well here.
    // }
}

MoveState Board::move(Piece *piece, Move move)
{
    // Store the current state for undo
    MoveState prevState = {
        piece,
        piece->xPosition,
        piece->yPosition,
        grid[move.x][move.y] // Piece at the destination (if any)
    };

    // Perform the move
    grid[move.x][move.y] = piece;                       // Place the piece in the new position
    grid[piece->xPosition][piece->yPosition] = nullptr; // Clear the old position

    // Update the piece's internal position
    piece->xPosition = move.x;
    piece->yPosition = move.y;

    return prevState; // Return the previous state for undo
}

void Board::undo(const MoveState &state)
{
    // Restore the moved piece's position
    grid[state.oldX][state.oldY] = state.movedPiece;                                      // Place the piece back to its original position
    grid[state.movedPiece->xPosition][state.movedPiece->yPosition] = state.capturedPiece; // Restore the captured piece (if any)

    // Update the moved piece's internal position
    state.movedPiece->xPosition = state.oldX;
    state.movedPiece->yPosition = state.oldY;
}
