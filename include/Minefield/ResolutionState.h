#pragma once
#include "GameState.h"

bool cellMatches(Cell const& a, Cell const& b);
class ResolutionState : public game::State
{
public:
    void handle(Game& game) override;

};

