#include <iostream>
#include <Minefield/board.h>

namespace BoardUtils
{

    void printColumnHeaders(Board const &board)
    {
        std::cout << "    ";
        if (board.grid.empty()) return;

        for (size_t x = 0; x < board.grid[0].size(); ++x)
        {
            int displayX = x + 1;
            std::cout << (displayX < 10 ? " " : "") << displayX << " ";
        }
        std::cout << '\n';

        std::cout << "   ";
        for (size_t x = 0; x < board.grid[0].size(); ++x)
        {
            std::cout << "---";
        }
        std::cout << '\n';
    }

    bool isMineVisibleForPlayer(Board const &board, Player const &player, size_t x, size_t y)
    {
        if (y >= board.grid.size() || x >= board.grid[y].size())
        {
            return false;
        }

        int displayX = x + 1;
        int displayY = y + 1;

        for (Mine const &mine : player.mines)
        {
            if (mine.location.x == displayX && mine.location.y == displayY)
            {
                return true;
            }
        }
        return false;
    }

    void printRow(Board const &board, Player const &player, size_t y)
    {
        if (y >= board.grid.size())
        {
            std::cerr << "Error: Y index out of bounds.\n";
            return;
        }

        int displayY = y + 1;
        std::cout << (displayY < 10 ? " " : "") << displayY << "| ";

        for (size_t x = 0; x < board.grid[y].size(); ++x)
        {
            if (isMineVisibleForPlayer(board, player, x, y))
            {
                std::cout << "*  ";
            }
            else
            {
                std::cout << getCellSymbol(board.grid[y][x]) << "  ";
            }
        }
        std::cout << '\n';
    }

    void printBoardPerPlayer(Board const &board, Player const &player)
    {
        printColumnHeaders(board);
        for (size_t y = 0; y < board.grid.size(); ++y)
        {
            printRow(board, player, y);
        }
    }

}