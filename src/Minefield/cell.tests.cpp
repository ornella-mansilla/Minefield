#include <gtest/gtest.h>
#include <Minefield/cell.h>
TEST(OrnellaSuiteTest, dummy_test)
{
    EXPECT_TRUE(true, true);
}

TEST(Cell, should_not_declare_a_cell_as_taken_by_default)
{
    Cell cell;
    EXPECT_FALSE(isCellTaken(cell)) << "A new Cell should not be marked as taken by default";
}
