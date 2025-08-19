#pragma once
#include <iostream>
#include <Minefield/player.h>
#include <Minefield/board.h>
namespace Init
{
	static constexpr int kMinBoardSize = 24;
	static constexpr int kMaxBoardSize = 50;
	static constexpr int kMinMines = 3;
	static constexpr int kMaxMines = 8;
	bool isBoardSizeValid(int size);
	bool isMineCountValid(int count);
	int getBoardDimension(std::string const& axisName);
	int readMineCount();
	void placeMinesForPlayer(Player& player, int count, int maxX, int maxY, Board& board);
	void printPlayerMines(Player const& player, int playerNumber);
	void printGameSetup(int rows, int columns, int mines);
	void initializeGrid(Board& board, int rows, int cols);
} // namespace Init