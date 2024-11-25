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
void Board::makeMove(Move move, const PieceType userSelection)
{
    if (move.moveType == MoveType::CASTLE)
    {
        this->move(move);                     // Move the king
        auto rookMove = rookCastleMove(move); // Get the rook's move
        this->move(rookMove);                 // Move the rook
        rookMove.piece->setMoved(true);
    }
    else if (move.moveType == MoveType::NORMAL)
    {
        // move capture
        if (m_grid[move.endCol][move.endRow] != nullptr &&
            m_grid[move.endCol][move.endRow]->m_color != move.piece->m_color)
        {
            auto &opponentPieces = (move.piece->m_color == Player::BLACK) ? m_whitePieces : m_blackPieces;
            opponentPieces.erase(m_grid[move.endCol][move.endRow]->m_name);
            delete m_grid[move.endCol][move.endRow];
        }
        this->move(move); // Execute the move
    }
    else if (move.moveType == MoveType::PROMOTION)
    {
        // promotion move capture
        if (m_grid[move.endCol][move.endRow] != nullptr &&
            m_grid[move.endCol][move.endRow]->m_color != move.piece->m_color)
        {
            auto &pieces = (move.piece->m_color == Player::BLACK) ? m_whitePieces : m_blackPieces;
            pieces.erase(m_grid[move.endCol][move.endRow]->m_name);
            delete m_grid[move.endCol][move.endRow];
        }

        Piece *newPiece;
        Player color = move.piece->m_color;

        switch (userSelection)
        {
        case PieceType::ROOK:
            ++this->numPromoted;
            newPiece = new Rook(move.piece->m_color, move.piece->m_col, move.piece->m_row, move.piece->m_name);
            break;

        case PieceType::BISHOP:
            // Code for BISHOP
            ++this->numPromoted;
            newPiece = new Bishop(move.piece->m_color, move.piece->m_col, move.piece->m_row, move.piece->m_name);
            break;

        case PieceType::KNIGHT: // Assuming you meant KNIGHT instead of repeating ROOK
                                // Code for KNIGHT
            ++this->numPromoted;
            newPiece = new Knight(move.piece->m_color, move.piece->m_col, move.piece->m_row, move.piece->m_name);
            break;

        case PieceType::QUEEN:
            // Code for QUEEN
            ++this->numPromoted;
            newPiece = new Queen(move.piece->m_color, move.piece->m_col, move.piece->m_row, move.piece->m_name);
            break;

        default:
            // Optional: Handle unexpected values
            break;
        }

        // add the new piece to its respective map
        auto &pieces = (color == Player::BLACK ? this->m_blackPieces : this->m_whitePieces);
        pieces[move.piece->m_name] = newPiece;

        delete move.piece;
        move.piece = newPiece;
        this->move(move); // Execute the move
    }
    move.piece->setMoved(true);
}

// input: move = [col,row]

// Used for Rook and Queen and Bishop
void Board::checkStarMoves(int startRow, int startCol, int rowStep, int colStep,
                           std::vector<Move> &moves, Player color) const
{
    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow >= 0 && currentRow < 8 && currentCol >= 0 && currentCol < 8)
    {
        if (m_grid[currentCol][currentRow] == nullptr)
        {
            moves.push_back({this->m_grid[startCol][startRow], currentCol, currentRow, MoveType::NORMAL}); // normal move
            currentRow += rowStep;
            currentCol += colStep;
        }
        else if (m_grid[currentCol][currentRow]->m_color != color)
        {
            moves.push_back({this->m_grid[startCol][startRow], currentCol, currentRow, MoveType::NORMAL}); // normal move
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
    for (const Move &validMove : m_validMoves)
    {
        highlight.setPosition(validMove.endRow * squareSize, validMove.endCol * squareSize);
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

KingPosition Board::getKingPosition(Player color) const
{
    return color == Player::BLACK ? this->m_blackKing : m_whiteKing;
}

// Ensure that no move creates a self-checked state.
std::vector<Move> Board::validatedMoves(std::vector<Move> potentialMoves)
{
    // Evaluate each move
    std::vector<Move> validMoves;

    for (const auto &move : potentialMoves)
    {
        Player color = move.piece->m_color;
        // if castle move
        // make both the king and rook movements.
        // then check if it is in check.
        // if not then add the king move to valid positions
        // undo both moves
        // for castling this function only checks if the final state is a check state after
        // castling and if the path is safe
        // in generate() we will check if there is a path to castle
        // and that neither the pieces have moved

        if (move.moveType == MoveType::CASTLE)
        {
            // Map king's castling destinations to rook path squares for validation
            const std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> castlePaths = {
                {{0, 6}, {{0, 5}, {0, 4}}},         // Top right rook (king-side)
                {{0, 2}, {{0, 3}, {0, 2}, {0, 1}}}, // Top left rook (queen-side)
                {{7, 6}, {{7, 5}, {7, 4}}},         // Bottom right rook (king-side)
                {{7, 2}, {{7, 3}, {7, 2}, {7, 1}}}  // Bottom left rook (queen-side)
            };

            // Check if move corresponds to a valid castling destination
            auto it = castlePaths.find({move.endCol, move.endRow});
            if (it != castlePaths.end())
            {
                // Check if all path squares are not under attack
                const auto &pathSquares = it->second;
                bool safe = std::all_of(
                    pathSquares.begin(),
                    pathSquares.end(),
                    [this, &move](const auto &square)
                    {
                        return !squareUnderAttack(square.first, square.second, move.piece->m_color);
                    });

                if (safe)
                {
                    // Make rook move and king move
                    auto rookUndoState = this->move(rookCastleMove(move));
                    auto kingUndoState = this->move(move);

                    // Check if the king is still safe after castling
                    if (!inCheck(color))
                    {
                        validMoves.push_back(move); // Valid castling move
                    }

                    // Undo the king move first, then the rook move
                    this->undo(kingUndoState);
                    this->undo(rookUndoState);
                }
            }
        }

        else
        {
            auto undoState = this->move(move);

            // Check if king is = in check
            if (!inCheck(color))
            {
                validMoves.push_back(move); // Valid move
            }

            this->undo(undoState);
        }
    }
    return validMoves;
}

Move Board::rookCastleMove(Move move)
{
    // no need to check if rook location exists because we do that in generateMoves()
    if (move.endCol == 0 && move.endRow == 6)
    {
        // top right rook
        auto rook = this->m_grid[0][7];
        // rook ends up at
        return Move(rook, 0, 5, MoveType::CASTLE);
    }
    else if (move.endCol == 0 && move.endRow == 2)
    {
        // top left rook
        auto rook = this->m_grid[0][0];
        // rook ends up at
        return Move(rook, 0, 3, MoveType::CASTLE);
    }
    else if (move.endCol == 7 && move.endRow == 2)
    {
        // bottom left rook
        auto rook = this->m_grid[7][0];
        // rook ends up at
        return Move(rook, 7, 3, MoveType::CASTLE);
    }
    else if (move.endCol == 7 && move.endRow == 6)
    {
        // bottom right rook
        auto rook = this->m_grid[7][7];
        // rook ends up at
        return Move(rook, 7, 5, MoveType::CASTLE);
    }

    std::cout << "error in rookCastleMove()" << std::endl;
    return Move(nullptr, -1, -1, MoveType::CASTLE);
}

bool Board::inCheck(Player color)
{
    // Determine the opponent's pieces based on the king's color
    KingPosition kingPosition = (color == Player::BLACK ? this->m_blackKing : this->m_whiteKing);

    return squareUnderAttack(kingPosition.col, kingPosition.row, color);
}

// pass in friendly color
bool Board::squareUnderAttack(int col, int row, Player color) const
{
    // Opponent pieces are stored in the opposite color's list
    Player opponentColor = (color == Player::BLACK ? Player::WHITE : Player::BLACK);
    const std::unordered_map<std::string, Piece *> &opponentPieces = (opponentColor == Player::BLACK ? this->m_blackPieces : this->m_whitePieces);

    for (auto &piece : opponentPieces)
    {
        // Use `->` because `piece.second` is a pointer to a Piece
        std::vector<Move> moves = piece.second->generateMoves(piece.second->m_col, piece.second->m_row, *this);

        for (auto move : moves)
        {
            if (move.endCol == col && move.endRow == row)
            {
                return true;
            }
        }
    }
    return false;
}

MoveState Board::move(Move move)
{
    // Store the current state for undo
    Player color = move.piece->m_color;
    KingPosition king = getKingPosition(color);

    MoveState prevState = {
        (move.piece->m_col == king.col && move.piece->m_row == king.row), // if we are moving the king
        move.piece,
        move.piece->m_col,
        move.piece->m_row,
        m_grid[move.endCol][move.endRow] // Piece at the destination (if any)
    };

    // Perform the move
    m_grid[move.endCol][move.endRow] = move.piece;      // Place the piece in the new position
    m_grid[move.piece->m_col][move.piece->m_row] = nullptr; // Clear the old position

    // If we are moving the king update king location variable
    if (move.piece->m_col == king.col && move.piece->m_row == king.row)
    {
        if (color == Player::BLACK)
        {
            this->m_blackKing.col = move.endCol;
            this->m_blackKing.row = move.endRow;
        }
        else if (color == Player::WHITE)
        {
            this->m_whiteKing.col = move.endCol;
            this->m_whiteKing.row = move.endRow;
        }
    }

    // Update the piece's internal position
    move.piece->m_col = move.endCol;
    move.piece->m_row = move.endRow;

    return prevState; // Return the previous state for undo
}

void Board::undo(const MoveState &state)
{
    Player color = state.movedPiece->m_color;

    // Restore the moved piece's position
    m_grid[state.oldCol][state.oldRow] = state.movedPiece;                      // Place the piece back to its original position
    m_grid[state.movedPiece->m_col][state.movedPiece->m_row] = state.capturedPiece; // Restore the captured piece (if any)

    // Update the moved piece's internal position
    state.movedPiece->m_col = state.oldCol;
    state.movedPiece->m_row = state.oldRow;

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