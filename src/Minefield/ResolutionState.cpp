#include <Minefield/GameContext.h>
#include <Minefield/ResolutionState.h>
#include <Minefield/EndGameState.h>
#include <Minefield/PlacementState.h>
#include <Minefield/cell.h>
#include <iostream>
#include <algorithm>

namespace resolutionUtils
{
    bool cellMatches(Cell const& a, Cell const& b)
    {
        return a.x == b.x && a.y == b.y;
    }

    void saveDestroyedMines(auto const& updatedMines, playerTypes::Attacker attacker, playerTypes::Defender defender)
    {
        bool saved = true;
        for (Mine const& oldMine : defender.raw().mines)
        {
            bool wasDestroyed
                = std::none_of(updatedMines.begin(), updatedMines.end(), [&oldMine](Mine const& m) { return cellMatches(m.location, oldMine.location); });

            if (wasDestroyed)
            {
                defender.raw().disabledMineSpots.push_back(oldMine.location);
            }
        }

        defender.raw().mines = updatedMines;
    }
    
    bool isHitSuccessful(std::string const& attackerName, playerTypes::Attacker attacker, playerTypes::Defender defender)
    {
        std::vector<Mine> updatedMines;
        bool hit = false;
        for (Mine const& mine : defender.raw().mines)
        {
            for (Cell const& guess : attacker.raw().guesses)
            {
                if (cellMatches(mine.location, guess))
                {
                    std::cout << attackerName << " hit a mine at (" << mine.location.x << ", " << mine.location.y << ")!\n";
                    hit = true;
                    break;
                }
            }
            if (!hit)
            {
                updatedMines.push_back(mine);
            }
        }
        saveDestroyedMines(updatedMines, attacker, defender);
        return hit;
    }

    bool selfDamage(playerTypes::Attacker attacker)
    {
        std::vector<Mine> updatedOwnMines;
        bool selfHit = false;
        for (Mine const& mine : attacker.raw().mines)
        {
            for (Cell const& guess : attacker.raw().guesses)
            {
                if (cellMatches(mine.location, guess))
                {
                    std::cout << "Oops! You guessed your own mine at (" << mine.location.x << ", " << mine.location.y << ")\n";
                    attacker.raw().disabledMineSpots.push_back(mine.location);
                    selfHit = true;
                    break;
                }
            }
            if (!selfHit)
            {
                updatedOwnMines.push_back(mine);
            }
        }

        attacker.raw().mines = updatedOwnMines;
        return selfHit;
    }

    void processGuesses(std::string const& attackerName, playerTypes::Attacker attacker, playerTypes::Defender defender, Board& board)
    {
        // before modify mines' lists
        auto const defenderMinesBefore = defender.raw().mines;
        auto const attackerMinesBefore = attacker.raw().mines;

        // update board if there was a mine
        for (auto const& guess : attacker.raw().guesses)
        {
            bool hitMine = std::any_of(defenderMinesBefore.begin(), defenderMinesBefore.end(), [&guess](Mine const& m) { return cellMatches(m.location, guess); })
                  || std::any_of(attackerMinesBefore.begin(), attackerMinesBefore.end(), [&guess](Mine const& m) { return cellMatches(m.location, guess); });

            // indexes to 0-based
            auto gy = static_cast<size_t>(guess.y - 1);
            auto gx = static_cast<size_t>(guess.x - 1);
            if (gy < board.grid.size() && gx < board.grid[gy].size())
            {
                board.grid[gy][gx].status = hitMine ? CellStatus::Taken : CellStatus::Empty;
            }
        }

        // now apply effects to lists (remove destroyed mines, self-damage, etc)
        isHitSuccessful(attackerName, attacker, defender);
        selfDamage(attacker);
    }

    std::vector<Mine> getMinesWithoutOverlaps(std::vector<Mine> const& playerMines, std::vector<Mine> const& otherPlayerMines)
    {
        std::vector<Mine> cleaned;
        for (Mine const& m : playerMines)
        {
            bool overlap = std::any_of(otherPlayerMines.begin(), otherPlayerMines.end(), [&m](Mine const& other) { return cellMatches(m.location, other.location); });
            if (!overlap)
            {
                cleaned.push_back(m);
            }
        }
        return cleaned;
    }

    void removeOverlappingMines(playerTypes::Player1 p1, playerTypes::Player2 p2)
    {
        auto p1Cleaned = getMinesWithoutOverlaps(p1.raw().mines, p2.raw().mines);
        auto p2Cleaned = getMinesWithoutOverlaps(p2.raw().mines, p1.raw().mines);

        if (p1.raw().mines.size() != p1Cleaned.size() || p2.raw().mines.size() != p2Cleaned.size())
        {
            std::cout << "Some overlapping mines were neutralized!\n";
        }

        p1.raw().mines = std::move(p1Cleaned);
        p2.raw().mines = std::move(p2Cleaned);
    }
}//namespace resolutionUtils

void ResolutionState::handle(Game& game)
{

    std::cout << "\n--- Resolution Phase ---\n";

    resolutionUtils::removeOverlappingMines(playerTypes::Player1{game.context.player1}, playerTypes::Player2{game.context.player2});

    resolutionUtils::processGuesses("Player 1", playerTypes::Attacker{game.context.player1}, playerTypes::Defender{game.context.player2}, game.context.board);
    resolutionUtils::processGuesses("Player 2", playerTypes::Attacker{game.context.player2}, playerTypes::Defender{game.context.player1}, game.context.board);

    // update remaining mines
    game.context.player1.remainingMines = game.context.player1.mines.size();
    game.context.player2.remainingMines = game.context.player2.mines.size();

    std::cout << "\nCurrent board state:\n";
    std::cout << "\nPlayer 1 remaining mines: " << std::endl;
    BoardUtils::printBoardPerPlayer(game.context.board, game.context.player1);
    std::cout << "\nPlayer 2 remaining mines: " << std::endl;
    BoardUtils::printBoardPerPlayer(game.context.board, game.context.player2);

    if (game.context.player1.remainingMines == 0 && game.context.player2.remainingMines == 0)
    {
        std::cout << "\nBoth players lost all mines at the same time!\n";
        game.logic.setState(std::make_unique<EndGameState>());
        return;
    }
    if (game.context.player1.remainingMines == 0 || game.context.player2.remainingMines == 0)
    {
        game.logic.setState(std::make_unique<EndGameState>());
        return;
    }
    game.logic.setState(std::make_unique<PlacementState>());
}
