#include <gtest/gtest.h>
#include <Minefield/ResolutionState.h>

namespace resolutionState::tests
{
class ResolutionStateSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
        guessMineA = {1,1,CellStatus::Bomb};
        guessMineB = {2,2,CellStatus::Bomb};
        guessMineC = {3,3,CellStatus::Bomb};
        emptyGuess = {4,5,CellStatus::Empty};
        wrongGuess = {6,7,CellStatus::Guess};
        takenGuess = {8,8,CellStatus::Taken};
    }

    std::string const playerName = static_cast<std::string>("testPlayer");
    Player player;
    playerTypes::Attacker attacker{player}; 
    playerTypes::Defender defenderA{player};
    playerTypes::Defender defenderB{player};
    Mine mineA{1, 1};
    Mine mineB{2, 2};
    Mine mineC{3, 3};
    Mine mineInEmptyGuess{4, 5};
    Cell guessMineA;
    Cell guessMineB;
    Cell guessMineC;
    Cell emptyGuess;
    Cell wrongGuess;
    Cell takenGuess;
};

using namespace resolutionUtils;

TEST(resolutionStateSuite, should_return_false_if_completly_different_cells)
{
    Cell cellA{8, 8, CellStatus::Bomb};
    Cell cellB{3, 1, CellStatus::Empty};
    EXPECT_FALSE(cellMatches(cellA, cellB));
}

TEST_F(ResolutionStateSuite, should_return_true_if_exactly_same_cell)
{
    Cell cellA{8, 8, CellStatus::Bomb};
    EXPECT_TRUE(cellMatches(cellA, cellA));
}

TEST_F(ResolutionStateSuite, should_return_true_if_same_info)
{
    Cell cellA{3, 1, CellStatus::Empty};
    Cell cellB{3, 1, CellStatus::Empty};
    EXPECT_TRUE(cellMatches(cellA, cellB));
}

TEST_F(ResolutionStateSuite, should_return_true_if_same_coords_but_different_status)
{
    Cell cellA{8, 8, CellStatus::Bomb};
    Cell cellB{8, 8, CellStatus::Empty};
    EXPECT_TRUE(cellMatches(cellA, cellB));
}

TEST_F(ResolutionStateSuite, should_true_if_attacker_and_defender_have_same_guess_mine)
{
    player.mines.push_back(mineA);
    player.guesses.push_back(guessMineA);
    EXPECT_TRUE(isHitSuccessful(playerName, attacker, defenderA));
}

TEST_F(ResolutionStateSuite, should_true_even_if_attacker_cell_status_is_empty_but_defender_has_mine_in_same_coordinate)
{
    attacker.raw().guesses.push_back(emptyGuess);
    defenderA.raw().mines.push_back(mineInEmptyGuess);
    EXPECT_TRUE(isHitSuccessful(playerName, attacker, defenderA));
}

TEST_F(ResolutionStateSuite, should_false_if_different_coordinate_and_empty_cell)
{
    attacker.raw().guesses.push_back(emptyGuess);
    defenderA.raw().mines.push_back(mineA);
    EXPECT_FALSE(isHitSuccessful(playerName, attacker, defenderA));
}

TEST_F(ResolutionStateSuite, should_return_false_when_compared_with_wrong_defender_but_true_when_compared_with_right_one)
{
    attacker.raw().guesses.push_back(emptyGuess);
    defenderB.raw().mines.push_back(mineC);
    ASSERT_FALSE(isHitSuccessful(playerName, attacker, defenderB));
    defenderA.raw().mines.push_back(mineA);
    attacker.raw().guesses.push_back(guessMineA);
    EXPECT_TRUE(isHitSuccessful(playerName, attacker, defenderA));
}
TEST_F(ResolutionStateSuite, should_true_if_more_than_one_coinciding_mine)
{
    attacker.raw().guesses.push_back(guessMineB);
    defenderA.raw().mines.push_back(mineA);
    ASSERT_FALSE(isHitSuccessful(playerName, attacker, defenderA));
    attacker.raw().guesses.push_back(guessMineA);
    attacker.raw().guesses.push_back(guessMineC);
    defenderA.raw().mines.push_back(mineB);
    defenderA.raw().mines.push_back(mineC);
    EXPECT_TRUE(isHitSuccessful(playerName, attacker, defenderA));
}
} // namespace ResolutionState::tests