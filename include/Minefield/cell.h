#pragma once

enum class CellStatus : char
{
    Empty = 'o',   // Empty cell
    Guess = '?',   // A guess has been made
    Bomb  = '*',   // Contains a mine
    Taken = 'x'    // Disabled cell (can no longer be used)
};


struct Cell
{
    int x;
    int y;
    CellStatus status;
};

bool isCellTaken(Cell const& cell);
char getCellSymbol(Cell const& cell);



