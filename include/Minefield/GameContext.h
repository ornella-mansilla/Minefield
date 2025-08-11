#pragma once
#include <memory>
#include <Minefield/board.h>
#include <Minefield/player.h>
struct Game;

namespace game
{
    class State;
    class Logic
    {
    public:
        void setState(std::unique_ptr<State> state);
        void run(Game &game);

    private:
        std::unique_ptr<State> mCurrentState;
    };
    struct Context
    {
        Board board;
        Player player1;
        Player player2;
        int columns;
        int rows;
        int mines;
    };

} // namespace game
struct Game
{
    game::Context context;
    game::Logic logic;
};
