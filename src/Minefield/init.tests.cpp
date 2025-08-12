#include <gtest/gtest.h>
#include <Minefield/init.h>

namespace init::tests
{
    TEST(Init, should_not_validate_out_of_range_axes_values)
    {
        int below_min_board_size = 24;
        int above_max_board_size = 51; 
        EXPECT_FALSE(Init::rangeValidation(below_min_board_size));
        EXPECT_FALSE(Init::rangeValidation(above_max_board_size)); 
    }
    TEST(Init, should_not_validate_out_of_range_mine_values)
    {
        int below_min_mine_count = 2;
        int above_max_mine_count = 9; 
        EXPECT_FALSE(Init::minesValidation(below_min_mine_count));
        EXPECT_FALSE(Init::minesValidation(above_max_mine_count)); 
    }

} // namespace minefield::init::tests