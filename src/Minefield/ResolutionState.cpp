#include <Minefield/GameContext.h>
#include <Minefield/ResolutionState.h>
#include <Minefield/EndGameState.h>
#include <Minefield/PlacementState.h>
#include <Minefield/cell.h>
#include <iostream>
#include <algorithm>

bool cellMatches(Cell const &a, Cell const &b)
{
    return a.x == b.x && a.y == b.y;
}

void checkHits(std::string const &attackerName, Player &attacker, Player &defender)
{
    std::vector<Mine> updatedMines;
    for (const auto &mine : defender.mines)
    {
        bool hit = false;
        for (const auto &guess : attacker.guesses)
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

    // save destroyed mines
    for (const auto &oldMine : defender.mines)
    {
        bool wasDestroyed = std::none_of(updatedMines.begin(), updatedMines.end(), [&oldMine](const Mine &m)
                                         { return cellMatches(m.location, oldMine.location); });

        if (wasDestroyed)
        {
            defender.disabledMineSpots.push_back(oldMine.location);
        }
    }

    defender.mines = updatedMines;
}
void checkSelfDamage(Player &attacker)
{
    std::vector<Mine> updatedOwnMines;
    for (const auto &mine : attacker.mines)
    {
        bool selfHit = false;
        for (const auto &guess : attacker.guesses)
        {
            if (cellMatches(mine.location, guess))
            {
                std::cout << "Oops! You guessed your own mine at (" << mine.location.x << ", " << mine.location.y << ")\n";
                attacker.disabledMineSpots.push_back(mine.location);
                selfHit = true;
                break;
            }
        }
        if (!selfHit)
        {
            updatedOwnMines.push_back(mine);
        }
    }

    attacker.mines = updatedOwnMines;
}

void processGuesses(std::string const &attackerName, Player &attacker, Player &defender, Board &board)
{
    // check if the attacker hit any mines of the defender
    checkHits(attackerName, attacker, defender);
    // check if the attacker guessed where he had a mine
    checkSelfDamage(attacker);

    // mark guessed cells as "Taken"
    for (const auto &guess : attacker.guesses)
    {
        int gx = guess.x - 1;
        int gy = guess.y - 1;
        board.grid[gy][gx].setStatus(CellStatus::Taken);
    }
}


std::vector<Mine> removeOverlaps(const std::vector<Mine>& mines, const std::vector<Mine>& otherMines)
{
    std::vector<Mine> cleaned;
    for (Mine const& m : mines)
    {
        bool overlap = std::any_of(otherMines.begin(), otherMines.end(), 
                                   [&m](Mine const& other) { return cellMatches(m.location, other.location); });
        if (!overlap)
        {
            cleaned.push_back(m);
        }
    }
    return cleaned;
}

void removeOverlappingMines(Player &p1, Player &p2)
{
    auto p1Cleaned = removeOverlaps(p1.mines, p2.mines);
    auto p2Cleaned = removeOverlaps(p2.mines, p1.mines);

    if (p1.mines.size() != p1Cleaned.size() || p2.mines.size() != p2Cleaned.size())
    {
        std::cout << "Some overlapping mines were neutralized!\n";
    }

    p1.mines = std::move(p1Cleaned);
    p2.mines = std::move(p2Cleaned);

}

void ResolutionState::handle(Game& game)
{

    std::cout << "\n--- Resolution Phase ---\n";

    removeOverlappingMines(game.context.player1, game.context.player2);

    processGuesses("Player 1", game.context.player1, game.context.player2, game.context.board);
    processGuesses("Player 2", game.context.player2, game.context.player1, game.context.board);

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
