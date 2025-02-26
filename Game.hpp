#ifndef TICTACTOE_GAME_HPP
#define TICTACTOE_GAME_HPP

#include <chrono>
#include "State.hpp"

class Game
{
private:
    Player currentPlayer;
    State currentState;

public:
    Game();

    void start();

    void move();

    int minimax(Player player);

    int minimaxAB(Player player, int alpha, int beta);

private:
    static void greet();

    void setUp();

    void humanMove();

    void botMove();

};

#endif //TICTACTOE_GAME_HPP
