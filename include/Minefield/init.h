#pragma once
#include <iostream>
#include <Minefield/player.h>
#include <Minefield/board.h>
namespace Init
{
    bool rangeValidation(int size);
    std::vector<int> initializeAxis(int size);
    bool minesValidation(int count);
    int getBoardDimension(std::string const& axisName);
    int readMineCount();
    void placeMinesForPlayer(Player& player, int count, int maxX, int maxY, Board& board);
    void printPlayerMines(Player const& player, int playerNumber);
    void printGameSetup(int rows, int columns, int mines);
    void initializeGrid(Board& board, int rows, int cols);
}