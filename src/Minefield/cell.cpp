#include <Minefield/cell.h>

bool isCellTaken(Cell const& cell)
{
    return cell.status == CellStatus::Taken;
}
char getCellSymbol(Cell const& cell)
{
    return static_cast<char>(cell.status);
}

