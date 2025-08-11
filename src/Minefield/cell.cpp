#include <Minefield/cell.h>

void Cell::setStatus(CellStatus newStatus) { status = newStatus; }
CellStatus Cell::getStatus() const { return status; }
bool Cell::isCellTaken() const { return status == CellStatus::Taken; }
char Cell::getCellSymbol() const { return static_cast<char>(status); }

