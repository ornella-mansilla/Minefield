#include <gtest/gtest.h>
#include <Minefield/GuessingState.h>
#include <Minefield/cell.h>
#include <Minefield/player.h>

namespace guessingState::tests
{
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

TEST(GuessingState, should_return_false_if_guess_is_not_in_player_guesses)
{
    Cell anotherGuess{8, 8, CellStatus::Bomb};
    auto player = makeBasePlayer();
    EXPECT_FALSE(guessUtils::isDuplicateGuess(player, anotherGuess));
}

TEST(GuessingState, should_detect_a_cell_thats_already_in_player_guesses)
{
    auto player = makeBasePlayer();
    Cell const& guessAlreadyMade = player.guesses.front();
    EXPECT_TRUE(guessUtils::isDuplicateGuess(player, guessAlreadyMade));
}

TEST(GuessingState, should_detect_a_cell_that_has_same_info_as_a_previous_cell)
{
    Cell duplicatedGuess{1, 1, CellStatus::Empty};
    auto player = makeBasePlayer();
    EXPECT_TRUE(guessUtils::isDuplicateGuess(player, duplicatedGuess));
}

TEST(GuessingState, should_detect_a_cell_that_has_same_coordinates_as_a_previous_cell_but_different_status)
{
    Cell similarGuess{2, 2, CellStatus::Taken};
    auto player = makeBasePlayer();
    EXPECT_TRUE(guessUtils::isDuplicateGuess(player, similarGuess));
}
} // namespace guessingState::tests