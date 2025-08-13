#pragma once
#include <iostream>
#include <Minefield/GameState.h>

class GuessingState : public game::State
{
public:
    void handle(Game& game) override;
};
namespace guessUtils
{
    bool getGuessCoordinates(int& x, int& y, Board const& board);
    bool isDuplicateGuess(Player const& player, Cell const& guess);
    void guess(Player& player, int& guesses, Game& game);
}; // namespace guessUtils