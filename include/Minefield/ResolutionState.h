#pragma once
#include <iostream>
#include "GameState.h"

class ResolutionState : public game::State
{
public:
    void handle(Game& game) override;

};
namespace resolutionUtils
{
    bool cellMatches(Cell const& a, Cell const& b);
    void checkHits(std::string const& attackerName, Player& attacker, Player& defender);
    void checkSelfDamage(Player& attacker);
    void processGuesses(std::string const& attackerName, Player& attacker, Player& defender, Board& board);
    std::vector<Mine> removeOverlaps(std::vector<Mine> const& mines, std::vector<Mine> const& otherMines);
    void removeOverlappingMines(Player& p1, Player& p2);
}