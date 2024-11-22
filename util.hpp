#pragma once
#include <stdint.h>


struct Move{
    int x;
    int y;

    Move(int x, int y) : x(x), y(y) {} // Constructor

};


void checkAdjacentMoves(int startRow, int startCol, int rowStep, int colStep,
                        std::vector<Move> &moves,
                        const std::vector<std::vector<Piece *>> &grid, std::string &color)
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
        else{
            break;
        }
    }
}