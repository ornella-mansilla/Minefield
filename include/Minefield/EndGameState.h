#pragma once
#include <Minefield/GameState.h>

class EndGameState : public game::State
{
public:
    void handle(Game& game) override;
};
