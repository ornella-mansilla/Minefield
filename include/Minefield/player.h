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
    using Attacker = StrongType<Player&, struct AttackerTag>;
    using Defender = StrongType<Player&, struct DefenderTag>;
    using Player1 = StrongType<Player&, struct Player1Tag>;
    using Player2 = StrongType<Player&, struct Player2Tag>;
} // namespace playerTypes
struct Mine
{
    Cell location;
    Mine(int x, int y) : location{x, y} {}
};