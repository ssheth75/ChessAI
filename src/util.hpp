#pragma once
#include <vector>
#include <stdint.h>

enum class Player
{
    WHITE,
    BLACK
};

enum class MoveType
{
    NORMAL,
    CASTLE,
    ENPASSANT,
    PROMOTION
};

enum class PieceType
{
    PAWN,
    ROOK, 
    QUEEN,
    KING,
    BISHOP,
    KNIGHT,
    NONE
};