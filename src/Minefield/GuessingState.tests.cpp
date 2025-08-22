#include <gtest/gtest.h>
#include <Minefield/GuessingState.h>
#include <Minefield/cell.h>
#include <Minefield/player.h>

namespace guessingState::tests
{
class GuessingStateSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
        cellInPlayerGuesses = {3, 3, CellStatus::Bomb};
        cellWithExactlySameInfoAsPlayerGuess = {3, 3, CellStatus::Bomb};
        cellWithSameCoordinatesAsPlayerGuessButDifferentStatus = {3, 3, CellStatus::Empty};
        cellOutOfPlayerGuesses = {6, 7, CellStatus::Guess};
        player.guesses.push_back(cellInPlayerGuesses);
    }
    std::string const playerName = static_cast<std::string>("testPlayer");
    Player player;
    Cell cellInPlayerGuesses;
    Cell cellWithExactlySameInfoAsPlayerGuess;
    Cell cellWithSameCoordinatesAsPlayerGuessButDifferentStatus;
    Cell cellOutOfPlayerGuesses;
};
TEST_F(GuessingStateSuite, should_return_false_if_guess_is_not_in_player_guesses)
{
    EXPECT_FALSE(guessUtils::isDuplicateGuess(player, cellOutOfPlayerGuesses));
}

TEST_F(GuessingStateSuite, should_detect_a_cell_thats_already_in_player_guesses)
{
    Cell const& guessAlreadyMade = player.guesses.front();
    EXPECT_TRUE(guessUtils::isDuplicateGuess(player, guessAlreadyMade));
}

TEST_F(GuessingStateSuite, should_detect_a_cell_that_has_same_info_as_a_previous_cell)
{
    EXPECT_TRUE(guessUtils::isDuplicateGuess(player, cellWithExactlySameInfoAsPlayerGuess));
}

TEST_F(GuessingStateSuite, should_detect_a_cell_that_has_same_coordinates_as_a_previous_cell_but_different_status)
{
    EXPECT_TRUE(guessUtils::isDuplicateGuess(player, cellWithSameCoordinatesAsPlayerGuessButDifferentStatus));
}
} // namespace guessingState::tests