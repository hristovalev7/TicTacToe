#include "Game.hpp"

Game::Game() : currentPlayer(Empty)
{}

void Game::start()
{
    greet();
    setUp();
    while (!currentState.isTerminal())
    {
        move();
    }
    if (currentState.oWins())
    {
        std::cout << "O wins!\n";
    }
    else if (currentState.xWins())
    {
        std::cout << "X wins!\n";
    }
    else
    {
        std::cout << "Tie!\n";
    }
}

void Game::greet()
{
    std::cout << "Who will go first?\n";
    std::cout << "0: Bot\n";
    std::cout << "1: Human\n";
}

void Game::setUp()
{
    int input;
    std::cin >> input;
    switch (input)
    {
        case 0:
            currentPlayer = O;
            break;
        case 1:
            currentPlayer = X;
            break;
        default:
            throw std::invalid_argument("Invalid input!");
    }
}

void Game::move()
{
    switch (currentPlayer)
    {
        case X:
            humanMove();
            break;
        case O:
            botMove();
            break;
        default:
            throw std::logic_error("Empty player can't make a move");
    }
}

void Game::humanMove()
{
    std::cout << "Human:\n";
    int x, y;
    std::cin >> x;
    std::cin.ignore(1);
    std::cin >> y;
    std::cin.ignore(1);
    while (!currentState.isFree(x, y))
    {
        std::cout << "Cell isn't free. Try again:\n";
        std::cin >> x;
        std::cin.ignore(1);
        std::cin >> y;
        std::cin.ignore(1);
    }
    currentState.place(x, y, X);
    currentPlayer = O;
}

void Game::botMove()
{
    std::cout << "Bot:\n";
    int bestValue{INT_MAX};
    std::pair<int, int> botMove{-1, -1};
    auto start = std::chrono::high_resolution_clock::now();
    for (std::pair<int, int> move: currentState.getPossibleMoves())
    {
        currentState.set(move.first, move.second, O);
//        int currentValue{minimax(X)};
        int currentValue{minimaxAB(X, INT_MIN, INT_MAX)};
        currentState.undo(move.first, move.second, O);
        if (currentValue < bestValue)
        {
            botMove = move;
        }
        bestValue = std::min(bestValue, currentValue);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration) << '\n';
    currentState.place(botMove.first, botMove.second, O);
    currentPlayer = X;
}

int Game::minimax(Player player)
{
    if (currentState.isTerminal())
    {
        return currentState.evaluate();
    }
    int value;
    if (player == X)
    {
        value = INT_MIN;
        for (std::pair<int, int> action: currentState.getPossibleMoves())
        {
            int x{action.first};
            int y{action.second};
            currentState.set(x, y, player);
            value = std::max(value, minimax(static_cast<Player>(-player)));
            currentState.undo(x, y, player);
        }
        return value;
    }
    else
    {
        value = INT_MAX;
        for (std::pair<int, int> action: currentState.getPossibleMoves())
        {
            int x{action.first};
            int y{action.second};
            currentState.set(x, y, player);
            value = std::min(value, minimax(static_cast<Player>(-player)));
            currentState.undo(x, y, player);
        }
        return value;
    }
}

int Game::minimaxAB(Player player, int alpha, int beta)
{
    if (currentState.isTerminal())
    {
        return currentState.evaluate();
    }
    int value;
    if (player == X)
    {
        value = INT_MIN;
        for (std::pair<int, int> action: currentState.getPossibleMoves())
        {
            int x{action.first};
            int y{action.second};
            currentState.set(x, y, player);
            value = std::max(value, minimaxAB(static_cast<Player>(-player), alpha, beta));
            currentState.undo(x, y, player);

            alpha = std::max(alpha, value);
            if (alpha >= beta)
            {
                break;
            }
        }
        return value;
    }
    else
    {
        value = INT_MAX;
        for (std::pair<int, int> action: currentState.getPossibleMoves())
        {
            int x{action.first};
            int y{action.second};
            currentState.set(x, y, player);
            value = std::min(value, minimaxAB(static_cast<Player>(-player), alpha, beta));
            currentState.undo(x, y, player);

            beta = std::min(beta, value);
            if (beta <= alpha)
            {
                break;
            }
        }
        return value;
    }
}

