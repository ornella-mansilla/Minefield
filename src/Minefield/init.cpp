#include <iostream>
#include <vector>
#include <Minefield/init.h>
#include <Minefield/cell.h>
#include <Minefield/player.h>

namespace Init
{
    static constexpr int kMinBoardSize = 24;
    static constexpr int kMaxBoardSize = 50;
    static constexpr int kMinMines = 3;
    static constexpr int kMaxMines = 8;

    bool rangeValidation(int size) { return size > kMinBoardSize && size <= kMaxBoardSize; }

    bool minesValidation(int count) { return count >= kMinMines && count <= kMaxMines; }

    int getBoardDimension(std::string const &axisName)
    {
        int size = 0;
        std::cout << "Enter number of " << axisName << " (between 25 and 50): ";
        std::cin >> size;
        while (!rangeValidation(size))
        {
            std::cout << "Invalid value. Please try again: ";
            std::cin >> size;
        }
        return size;
    }

    int readMineCount()
    {
        int count = 0;
        std::cout << "Enter number of mines (between 3 and 8): ";
        std::cin >> count;
        while (!minesValidation(count))
        {
            std::cout << "Invalid value. Please try again: ";
            std::cin >> count;
        }
        return count;
    }

    void printRemainingMines(Player const &player)
    {
        std::cout << "\nRemaining mines: " << player.remainingMines << "\n";
        std::cout << "You may place your " << player.remainingMines << " mines now.\n";
    }

    bool getMineCoordinates(int &x, int &y, int maxX, int maxY)
    {
        std::cout << "Enter X coordinate (1-" << maxX << "): ";
        std::cin >> x;
        std::cout << "Enter Y coordinate (1-" << maxY << "): ";
        std::cin >> y;

        return (x >= 1 && x <= maxX && y >= 1 && y <= maxY);
    }

    bool isValidPlacement(Board const &board, Player const &player, int x, int y)
    {
        int indexX = x - 1;
        int indexY = y - 1;

        if (isCellTaken(board.grid[indexY][indexX]))
        {
            std::cout << "That cell is taken from a previous guess. Try again.\n";
            return false;
        }

        for (const auto &disabled : player.disabledMineSpots)
        {
            if (disabled.x == x && disabled.y == y)
            {
                std::cout << "You lost a mine there before. You can't reuse that cell.\n";
                return false;
            }
        }

        for (const auto &mine : player.mines)
        {
            if (mine.location.x == x && mine.location.y == y)
            {
                std::cout << "Already placed a mine there this turn. Try again.\n";
                return false;
            }
        }

        return true;
    }

    void placeMinesForPlayer(Player &player, int count, int maxX, int maxY, Board &board)
    {
        player.mines.clear();
        printRemainingMines(player);

        while (player.mines.size() < static_cast<size_t>(player.remainingMines))
        {
            int x = 0;
            int y = 0;
            std::cout << "\nPlacing mine #" << (player.mines.size() + 1) << " of " << player.remainingMines << "\n";
            if (!getMineCoordinates(x, y, maxX, maxY))
            {
                std::cout << "Invalid position. Try again.\n";
                continue;
            }

            if (!isValidPlacement(board, player, x, y))
            {
                continue; // invalid placement, retry
            }

            player.mines.push_back(Mine(x, y));
        }
    }

    void printPlayerMines(Player const &player, int playerNumber)
    {
        std::cout << "\nMines of the player " << playerNumber << ":\n";
        for (size_t i = 0; i < player.mines.size(); ++i)
        {
            std::cout << "Mine #" << (i + 1) << ": (" << player.mines[i].location.x << "," << player.mines[i].location.y << ")\n";
        }
    }

    void printGameSetup(int rows, int columns, int mines)
    {
        std::cout << "Setup completed:\n";
        std::cout << "Board of " << rows << " rows x " << columns << " columns\n";
        std::cout << "Each player has " << mines << " mines per turn\n";
    }

    void initializeGrid(Board &board, int rows, int cols)
    {
        board.grid.resize(rows);

        for (int y = 0; y < rows; ++y)
        {
            board.grid[y].resize(cols);
            for (int x = 0; x < cols; ++x)
            {
                board.grid[y][x] = Cell{x + 1, y + 1, CellStatus::Empty};
            }
        }
    }
}
