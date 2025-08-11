#include <Minefield/GameContext.h>
#include <Minefield/EndGameState.h>
#include <Minefield/PlacementState.h>
#include <Minefield/board.h>
#include <iostream>

void EndGameState::handle(Game& game)
{
    std::cout << "\n--- Game Over ---\n";

    int p1 = game.context.player1.remainingMines;
    int p2 = game.context.player2.remainingMines;

    if (p1 > p2)
    {
        std::cout << "Player 1 wins!\n";
        game.logic.setState(nullptr);
    } else if (p2 > p1){
        std::cout << "Player 2 wins!\n";
        game.logic.setState(nullptr);
    } else{
        std::cout << "It's a draw!\n";
        game.logic.setState(nullptr);
    }
}
