#include "Board.hpp"
#include <iostream>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"

Board::Board() : m_whiteKing(7, 4), m_blackKing(0, 4)
{
    setupBoard();
}

// input: move = [col,row]
void Board::makeMove(Piece *piece, Move move)
{

    // Capture logic: delete the opponent's piece if present
    if (m_grid[move.col][move.row] != nullptr && m_grid[move.col][move.row]->getColor() != piece->getColor())
    {
        auto &pieces = (m_grid[move.col][move.row]->getColor() == Player::BLACK) ? m_blackPieces : m_whitePieces;
        pieces.erase(m_grid[move.col][move.row]->name); // Erase from the appropriate map
        delete m_grid[move.col][move.row];              // Remove the captured piece
    }

    this->move(piece, move);

    // if we just moved a king piece then update KingPosition for that piece
    if (piece->getType() == "King")
    {
        if (piece->getColor() == Player::BLACK)
        {
            m_blackKing.col = move.col;
            m_blackKing.row = move.row;
        }
        else if (piece->getColor() == Player::WHITE)
        {
            m_whiteKing.col = move.col;
            m_whiteKing.row = move.row;
        }
    }
}

// input: move = [col,row]
Piece *Board::getPieceAt(int x, int y) const
{
    // Only access if piece present
    if (m_grid[x][y])
    {
        std::cout << "piece type: " << m_grid[x][y]->getType() << std::endl;
        return m_grid[x][y];
    }

    return nullptr;
}
// Used for Rook and Queen
void Board::checkStarMoves(int startRow, int startCol, int rowStep, int colStep,
                           std::vector<Move> &moves, Player color) const
{
    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow >= 0 && currentRow < 8 && currentCol >= 0 && currentCol < 8)
    {
        if (m_grid[currentCol][currentRow] == nullptr)
        {
            moves.push_back({currentCol, currentRow});
            currentRow += rowStep;
            currentCol += colStep;
        }
        else if (m_grid[currentCol][currentRow]->getColor() != color)
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

void Board::draw(sf::RenderWindow &window)
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
            window.draw(square);
        }
    }

    // Highlight valid moves
    sf::RectangleShape highlight(sf::Vector2f(squareSize, squareSize));
    highlight.setFillColor(sf::Color(0, 255, 0, 100)); // Semi-transparent green
    for (const Move &move : m_validMoves)
    {
        highlight.setPosition(move.row * squareSize, move.col * squareSize);
        window.draw(highlight);
    }

    // Draw pieces
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = m_grid[row][col];
            if (piece)
            {
                piece->draw(window, col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}

void Board::setupBoard()
{
    // Initialize the m_grid with nullptr (empty squares)
    m_grid = std::vector<std::vector<Piece *>>(8, std::vector<Piece *>(8, nullptr));

    // Place black pieces
    m_grid[0][0] = new Rook(Player::BLACK, 0, 0, "br1");
    m_blackPieces["br1"] = m_grid[0][0];
    m_grid[0][1] = new Knight(Player::BLACK, 0, 1, "bn1");
    m_blackPieces["bn1"] = m_grid[0][1];
    m_grid[0][2] = new Bishop(Player::BLACK, 0, 2, "bb1");
    m_blackPieces["bb1"] = m_grid[0][2];
    m_grid[0][3] = new Queen(Player::BLACK, 0, 3, "bq");
    m_blackPieces["bq"] = m_grid[0][3];
    m_grid[0][4] = new King(Player::BLACK, 0, 4, "bk");
    m_blackPieces["bk"] = m_grid[0][4];
    m_grid[0][5] = new Bishop(Player::BLACK, 0, 5, "bb2");
    m_blackPieces["bb2"] = m_grid[0][5];
    m_grid[0][6] = new Knight(Player::BLACK, 0, 6, "bn2");
    m_blackPieces["bn2"] = m_grid[0][6];
    m_grid[0][7] = new Rook(Player::BLACK, 0, 7, "br2");
    m_blackPieces["br2"] = m_grid[0][7];

    for (int col = 0; col < 8; ++col)
    {
        m_grid[1][col] = new Pawn(Player::BLACK, 1, col, "bp" + std::to_string(col + 1));
        m_blackPieces["bp" + std::to_string(col + 1)] = m_grid[1][col];

        m_grid[6][col] = new Pawn(Player::WHITE, 6, col, "wp" + std::to_string(col + 1));
        m_whitePieces["wp" + std::to_string(col + 1)] = m_grid[6][col];
    }

    // Place white pieces
    m_grid[7][0] = new Rook(Player::WHITE, 7, 0, "wr1");
    m_whitePieces["wr1"] = m_grid[7][0];
    m_grid[7][1] = new Knight(Player::WHITE, 7, 1, "wn1");
    m_whitePieces["wn1"] = m_grid[7][1];
    m_grid[7][2] = new Bishop(Player::WHITE, 7, 2, "wb1");
    m_whitePieces["wb1"] = m_grid[7][2];
    m_grid[7][3] = new Queen(Player::WHITE, 7, 3, "wq");
    m_whitePieces["wq"] = m_grid[7][3];
    m_grid[7][4] = new King(Player::WHITE, 7, 4, "wk");
    m_whitePieces["wk"] = m_grid[7][4];
    m_grid[7][5] = new Bishop(Player::WHITE, 7, 5, "wb2");
    m_whitePieces["wb2"] = m_grid[7][5];
    m_grid[7][6] = new Knight(Player::WHITE, 7, 6, "wn2");
    m_whitePieces["wn2"] = m_grid[7][6];
    m_grid[7][7] = new Rook(Player::WHITE, 7, 7, "wr2");
    m_whitePieces["wr2"] = m_grid[7][7];
}

KingPosition Board::getKingPosition(Player color)
{
    return color == Player::BLACK ? this->m_blackKing : m_whiteKing;
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

bool Board::inCheck(Player kingColor)
{
    // Determine the opponent's pieces based on the king's color
    return pieceUnderAttack(kingColor);

    return false; // The king is not in check
}

bool Board::pieceUnderAttack(Player color)
{
    // Opponent pieces are stored in the opposite color's list
    std::unordered_map<std::string, Piece *> &opponentPieces = (color == Player::BLACK ? this->m_whitePieces : this->m_blackPieces);
    KingPosition king = getKingPosition(color);

    for (auto &piece : opponentPieces)
    {
        // Use `->` because `piece.second` is a pointer to a Piece
        std::vector<Move> moves = piece.second->generateMoves(piece.second->col, piece.second->row, *this);

        for (auto move : moves)
        {
            if (move.col == king.col && move.row == king.row)
            {
                return true;
            }
        }
    }

    return false;
}

MoveState Board::move(Piece *piece, Move move)
{
    // Store the current state for undo
    Player color = piece->getColor();
    KingPosition king = getKingPosition(color);

    MoveState prevState = {
        (piece->col == king.col && piece->row == king.row), // if we are moving the king
        piece,
        piece->col,
        piece->row,
        m_grid[move.col][move.row] // Piece at the destination (if any)
    };

    // Perform the move
    m_grid[move.col][move.row] = piece;       // Place the piece in the new position
    m_grid[piece->col][piece->row] = nullptr; // Clear the old position

    // If we are moving the king update king location variable
    if (piece->col == king.col && piece->row == king.row)
    {
        if (color == Player::BLACK)
        {
            this->m_blackKing.col = move.col;
            this->m_blackKing.row = move.row;
        }
        else if (color == Player::WHITE)
        {
            this->m_whiteKing.col = move.col;
            this->m_whiteKing.row = move.row;
        }
    }

    // Update the piece's internal position
    piece->col = move.col;
    piece->row = move.row;

    return prevState; // Return the previous state for undo
}

void Board::undo(const MoveState &state)
{
    Player color = state.movedPiece->getColor();

    // Restore the moved piece's position
    m_grid[state.oldCol][state.oldRow] = state.movedPiece;                      // Place the piece back to its original position
    m_grid[state.movedPiece->col][state.movedPiece->row] = state.capturedPiece; // Restore the captured piece (if any)

    // Update the moved piece's internal position
    state.movedPiece->col = state.oldCol;
    state.movedPiece->row = state.oldRow;

    // if we just moved the king
    if (state.isKing)
    {
        if (color == Player::BLACK)
        {
            this->m_blackKing.col = state.oldCol;
            this->m_blackKing.row = state.oldRow;
        }
        else if (color == Player::WHITE)
        {
            this->m_whiteKing.col = state.oldCol;
            this->m_whiteKing.row = state.oldRow;
        }
    }
}

Player opponent(Player color)
{
    return (color == Player::BLACK) ? Player::WHITE : Player::BLACK;
}