#pragma once
#include <vector>
#include <Minefield/strongType.h>
#include <Minefield/cell.h>
struct Mine;
struct Player
{
    int id; // Player ID
    std::vector<Mine> mines;
    std::vector<Cell> guesses;
    std::vector<Cell> disabledMineSpots; // locations where own mines were destroyed
    int remainingMines; // the number of mines the player can still place or use
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
struct Mine
{
    Cell location;
    Mine(int x, int y) : location{x, y} {}
};