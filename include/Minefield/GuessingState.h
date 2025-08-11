#pragma once
#include <Minefield/GameState.h>

class GuessingState : public game::State
{
public:
    void handle(Game& game) override;
};
