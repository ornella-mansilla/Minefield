#pragma once
#include <Minefield/GameContext.h>

struct Game; 

class game::State
{
public:
    virtual ~State() = default;
    virtual void handle(Game& game) = 0;
};
