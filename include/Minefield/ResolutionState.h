#pragma once
#include <iostream>
#include "strongType.h"
#include "player.h"
#include "GameState.h"

class ResolutionState : public game::State
{
public:
    void handle(Game& game) override;

};

namespace resolutionUtils
{
    bool cellMatches(Cell const& a, Cell const& b);
    bool isHitSuccessful(std::string const& attackerName, playerTypes::Attacker attacker, playerTypes::Defender defender);
    bool selfDamage(playerTypes::Attacker attacker);
    void processGuesses(std::string const& attackerName, playerTypes::Attacker attacker, playerTypes::Defender defender, Board& board);
    std::vector<Mine> getMinesWithoutOverlaps(std::vector<Mine> const& playerMines, std::vector<Mine> const& otherPlayerMines);
    void removeOverlappingMines(playerTypes::Player1 p1, playerTypes::Player2 p2);
}
