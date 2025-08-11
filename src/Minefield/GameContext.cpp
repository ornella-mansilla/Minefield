#include <Minefield/GameContext.h>
#include <Minefield/GameState.h>

void game::Logic::setState(std::unique_ptr<State> state)
{
    mCurrentState = std::move(state);
}

void game::Logic::run(Game& game)
{
    while (mCurrentState)
    {
        mCurrentState->handle(game);
    }
}
