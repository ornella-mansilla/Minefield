#pragma once
#include <iostream>
#include "strongType.h"
#include "GameState.h"

class ResolutionState : public game::State
{
public:
    void handle(Game& game) override;

};
namespace playerTypes
{
    struct AttackerTag{};
    struct DefenderTag{};
    struct Player1Tag{};
    struct Player2Tag{};

    using Attacker = StrongType<Player&, AttackerTag>;
    using Defender = StrongType<Player&, DefenderTag>;
    using Player1 = StrongType<Player&, Player1Tag>;
    using Player2 = StrongType<Player&, Player2Tag>;
}
namespace resolutionUtils
{
    bool cellMatches(Cell const& a, Cell const& b);
    bool isHitSuccessful(std::string const& attackerName, playerTypes::Attacker attacker, playerTypes::Defender defender);
    bool selfDamage(playerTypes::Attacker attacker);
    void processGuesses(std::string const& attackerName, playerTypes::Attacker attacker, playerTypes::Defender defender, Board& board);
    std::vector<Mine> getMinesWithoutOverlaps(std::vector<Mine> const& playerMines, std::vector<Mine> const& otherPlayerMines);
    void removeOverlappingMines(playerTypes::Player1 p1, playerTypes::Player2 p2);
    }
