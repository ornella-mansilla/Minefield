#include <Minefield/GameContext.h>
#include <Minefield/GuessingState.h>
#include <Minefield/ResolutionState.h>
#include <Minefield/board.h>
#include <Minefield/init.h>
#include <Minefield/cell.h>
#include <iostream>

namespace guessUtils
{
    bool getGuessCoordinates(int& x, int& y, Board const& board)
    {
        std::cout << "Enter X: ";

        std::cin >> x;
        std::cout << "Enter Y: ";
        std::cin >> y;

        return (y >= 1 && y <= static_cast<int>(board.grid.size()) && x >= 1 && x <= static_cast<int>(board.grid[0].size()));
    }


    bool isDuplicateGuess(Player const& player, Cell const& guess)
    {
        for (Cell const& g : player.guesses)
        {
            if (resolutionUtils::cellMatches(g, guess))
            {
                std::cout << "You already guessed that. Try again.\n";
                return true; // Found a duplicate guess
            }
        }
        return false; // No duplicate found
    }
    void guess(Player & player, int& guesses, Game& game)
    {
        std::cout << "Player " << player.id << ": You have " << guesses << " guesses. \n";

        while (player.guesses.size() < static_cast<size_t>(guesses))
        {
            int x = 0;
            int y = 0;
            std::cout << "\nGuess #" << (player.guesses.size() + 1) << " of " << guesses << "\n";
            if (!getGuessCoordinates(x, y, game.context.board) || isCellTaken(Cell{x,y}))
            {
                std::cout << "Invalid guess location. Try again.\n";
                continue;
            }
            Cell guess{x, y, CellStatus::Guess};
            
            if (!isDuplicateGuess(player, guess))
            {
                player.guesses.push_back(guess); // add the guess if it's valid and not a duplicate
                game.context.board.grid[y-1][x-1] = guess; // 
            }
        }
    }
}//namespace guessUtils
void GuessingState::handle(Game& game)
{
    std::cout << "\n--- Guessing Phase ---\n";

    game.context.player1.guesses.clear();
    game.context.player2.guesses.clear();

    int guesses1 = game.context.player2.mines.size();
    int guesses2 = game.context.player1.mines.size();

    guessUtils::guess(game.context.player1, guesses1, game);
    BoardUtils::printBoardPerPlayer(game.context.board, game.context.player1);
    guessUtils::guess(game.context.player2, guesses2, game);
    BoardUtils::printBoardPerPlayer(game.context.board, game.context.player2);

    game.logic.setState(std::make_unique<ResolutionState>());
}



