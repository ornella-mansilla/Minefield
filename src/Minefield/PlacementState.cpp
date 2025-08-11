#include <Minefield/GameContext.h>
#include <Minefield/PlacementState.h>
#include <Minefield/GuessingState.h>
#include <Minefield/init.h>
#include <Minefield/board.h>
#include <iostream>

void PlacementState::handle(Game& game)
{
    std::cout << "\n--- Placement Phase ---\n";

    std::cout << "Player 1, place your mines:\n";
    Init::placeMinesForPlayer(game.context.player1, game.context.player1.remainingMines, game.context.columns, game.context.rows, game.context.board);
    BoardUtils::printBoardPerPlayer(game.context.board, game.context.player1);

    std::cout << "\nPlayer 2, place your mines:\n";
    Init::placeMinesForPlayer(game.context.player2, game.context.player2.remainingMines, game.context.columns, game.context.rows, game.context.board);
    BoardUtils::printBoardPerPlayer(game.context.board, game.context.player2);
    game.logic.setState(std::make_unique<GuessingState>());
}
