#ifndef TICTACTOE_GAME_HPP
#define TICTACTOE_GAME_HPP

#include "State.hpp"

class Game
{
private:
    Player currentPlayer;
public:
    State currentState;

    Game();

    void start();

    void move();

    int minimax(Player player);

private:
    static void greet();

    void setUp();

    void humanMove();

    void botMove();

};

#endif //TICTACTOE_GAME_HPP
