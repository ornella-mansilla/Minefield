#include <gtest/gtest.h>
#include <Minefield/ResolutionState.h>

namespace ResolutionState::tests
{
using namespace resolutionUtils;
static Player makeBasePlayer()
{
    Cell guessA{1, 1, CellStatus::Empty};
    Cell guessB{2, 2, CellStatus::Bomb};
    Player testPlayer;
    testPlayer.id = 1;
    testPlayer.guesses.push_back(guessA);
    testPlayer.guesses.push_back(guessB);
    return testPlayer;
}

TEST(ResolutionState, should_return_false_if_completly_different_cells)
{
    Cell cellA{8, 8, CellStatus::Bomb};
    Cell cellB{3, 1, CellStatus::Empty};
    EXPECT_FALSE(cellMatches(cellA, cellB));
}

TEST(ResolutionState, should_return_true_if_exactly_same_cell)
{
    Cell cellA{8, 8, CellStatus::Bomb};
    EXPECT_TRUE(cellMatches(cellA, cellA));
}

TEST(ResolutionState, should_return_true_if_same_info)
{
    Cell cellA{3, 1, CellStatus::Empty};
    Cell cellB{3, 1, CellStatus::Empty};
    EXPECT_TRUE(cellMatches(cellA, cellB));
}

TEST(ResolutionState, should_return_true_if_same_coords_but_different_status)
{
    Cell cellA{8, 8, CellStatus::Bomb};
    Cell cellB{8, 8, CellStatus::Empty};
    EXPECT_TRUE(cellMatches(cellA, cellB));
}

TEST(isHitSuccessful, should_return_true_if_same_coords_but_different_status)
{
    auto attacker = makeBasePlayer();
    auto defender = makeBasePlayer();
    isHitSuccessful("juan", playerTypes::Attacker{attacker}, playerTypes::Defender{defender});
    //TODO: finish this test.
}
} // namespace ResolutionState::tests