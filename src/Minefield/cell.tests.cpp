#include <gtest/gtest.h>
#include <Minefield/cell.h>
namespace cell::tests
{
    TEST(isCellTaken, should_detect_a_taken_cell)
    {
        Cell cell{1,1,CellStatus::Taken};
        EXPECT_TRUE(isCellTaken(cell));
    }

    TEST(isCellTaken, coordinate_values_should_not_affect_function_result)
    {
        Cell cell{-10, 9999, CellStatus::Taken};
        EXPECT_TRUE(isCellTaken(cell));
    }

    TEST(isCellTaken, should_not_treat_bomb_as_taken)
    {
        Cell cell{1, 1, CellStatus::Bomb};
        EXPECT_FALSE(isCellTaken(cell));
    }

    TEST(isCellTaken, should_not_treat_empty_as_taken)
    {
        Cell cell{1, 1, CellStatus::Empty};
        EXPECT_FALSE(isCellTaken(cell));
    }

    TEST(isCellTaken, should_not_treat_guess_as_taken)
    {
        Cell cell{1, 1, CellStatus::Guess};
        EXPECT_FALSE(isCellTaken(cell));
    }

    TEST(getCellSymbol, should_bring_same_cell_symbol)
    {
        Cell cell{1, 1, CellStatus::Taken};
        EXPECT_TRUE(getCellSymbol(cell) == static_cast<char>(CellStatus::Taken));
    }

    TEST(getCellSymbol, should_not_bring_anything_else_but_the_original_symbol)
    {
        Cell cell{1, 1, CellStatus::Empty};
        EXPECT_FALSE(getCellSymbol(cell) != static_cast<char>(CellStatus::Empty));
    }
    }
