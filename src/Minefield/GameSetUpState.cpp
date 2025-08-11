#include <Minefield/GameContext.h>
#include <Minefield/GameSetUpState.h>
#include <Minefield/PlacementState.h>
#include <Minefield/init.h>
#include <iostream>

void GameSetUpState::handle(Game& game)
{
    std::cout << "=== Game Setup ===\n";

    game.context.columns = Init::getBoardDimension("columns");
    game.context.rows = Init::getBoardDimension("rows");
    game.context.mines = Init::readMineCount();

    game.context.player1.remainingMines = game.context.mines;
    game.context.player1.id = 1;
    game.context.player2.remainingMines = game.context.mines;
    game.context.player2.id = 2;

    Init::printGameSetup(game.context.rows, game.context.columns, game.context.mines);
    Init::initializeGrid(game.context.board, game.context.rows, game.context.columns);

    game.logic.setState(std::make_unique<PlacementState>());
}
