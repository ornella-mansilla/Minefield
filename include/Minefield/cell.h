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

    void setStatus(CellStatus newStatus);
    CellStatus getStatus() const;
    bool isCellTaken() const;
    char getCellSymbol() const;
};



