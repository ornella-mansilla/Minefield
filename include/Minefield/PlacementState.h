#pragma once
#include <Minefield/GameState.h>

class PlacementState : public game::State
{
public:
    void handle(Game& game) override;
};
