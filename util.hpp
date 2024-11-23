#pragma once
#include <vector>
#include <stdint.h>

struct Move
{
    int col;
    int row;

    Move(int col, int row) : col(col), row(row) {}
};

enum class Player
{
    WHITE,
    BLACK
};