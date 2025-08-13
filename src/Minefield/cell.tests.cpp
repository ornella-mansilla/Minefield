#include <gtest/gtest.h>
#include <Minefield/cell.h>
namespace cell::tests
{
    //TEST(OrnellaSuiteTest, dummy_test)
    //{
    //    EXPECT_TRUE(true, true);
    //}

    TEST(Cell, should_not_declare_a_cell_as_taken_by_default)
    {
        Cell cell;
       /* cell.status = CellStatus::Taken;*/
        EXPECT_FALSE(isCellTaken(cell)) << "A new Cell should not be marked as taken by default";
    }

}
