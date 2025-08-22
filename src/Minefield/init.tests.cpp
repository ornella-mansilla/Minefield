#include <gtest/gtest.h>
#include <Minefield/init.h>

namespace init::tests
{ 
    TEST(isBoardSizeValid, should_validate_values_inside_range)
    {
        int valueInsideRange = Init::kMinBoardSize + 10;
        EXPECT_TRUE(Init::isBoardSizeValid(valueInsideRange));
    }

    TEST(isBoardSizeValid, should_validate_edge_value_max)
    {
        EXPECT_TRUE(Init::isBoardSizeValid(Init::kMaxBoardSize));
    }

    TEST(isBoardSizeValid, should_validate_edge_value_min)
    {
        EXPECT_TRUE(Init::isBoardSizeValid(Init::kMinBoardSize));
    }

    TEST(isBoardSizeValid, should_not_validate_upper_out_of_range_axis_values)
    {
        int valueAboveMaxSize = Init::kMaxBoardSize + 10;
        EXPECT_FALSE(Init::isBoardSizeValid(valueAboveMaxSize));
    }

    TEST(isBoardSizeValid, should_not_validate_lower_out_of_range_axis_values)
    {
        int valueBelowMinSize = Init::kMinBoardSize - 10;
        EXPECT_FALSE(Init::isBoardSizeValid(valueBelowMinSize));
    }

    TEST(isBoardSizeValid, should_not_validate_negative_values)
    {
        EXPECT_FALSE(Init::isBoardSizeValid(-1));
    }

    TEST(isMineCountValid, should_validate_values_inside_range)
    {
        int valueInsideRange = Init::kMinMines + 1;
        EXPECT_TRUE(Init::isMineCountValid(valueInsideRange));
    }

    TEST(isMineCountValid, should_validate_edge_value_max)
    {
        EXPECT_TRUE(Init::isMineCountValid(Init::kMaxMines));
    }

    TEST(isMineCountValid, should_validate_edge_value_min)
    {
        EXPECT_TRUE(Init::isMineCountValid(Init::kMinMines));
    }

    TEST(isMineCountValid, should_not_validate_upper_out_of_range_axis_values)
    {
        int valueAboveMaxSize = Init::kMaxMines + 10;
        EXPECT_FALSE(Init::isMineCountValid(valueAboveMaxSize));
    }

    TEST(isMineCountValid, should_not_validate_lower_out_of_range_axis_values)
    {
        int valueBelowMinSize = Init::kMinMines - 10;
        EXPECT_FALSE(Init::isMineCountValid(valueBelowMinSize));
    }

    TEST(isMineCountValid, should_not_validate_negative_values)
    {
        EXPECT_FALSE(Init::isMineCountValid(-1));
    }
}