#include "Game.hpp"

Game::Game() : currentPlayer(X), human(X), bot(O)
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
    currentState.place(x, y, human);
    currentPlayer = bot;
}

void Game::botMove()
{
    std::cout << "Bot:\n";
    int bestValue{INT_MAX};
    std::pair<int, int> botMove{-1, -1};
    for (std::pair<int, int> move: currentState.getPossibleMoves())
    {
        currentState.set(move.first, move.second, bot);
        int currentValue{minimax(human)};
        currentState.undo(move.first, move.second, bot);
        if (currentValue < bestValue)
        {
            botMove = move;
        }
        bestValue = std::min(bestValue, currentValue);
    }
    currentState.place(botMove.first, botMove.second, bot);
    currentPlayer = human;
}

void Game::botMove2()
{
    std::cout << "Bot:\n";
    //TODO: algorithm here
    std::pair<int, int> bestMove{currentState.getPossibleMoves().begin()->first, currentState.getPossibleMoves().begin()->second};
    currentState.set(bestMove.first, bestMove.second, O);
    int bestValue{currentState.evaluate()};
    currentState.undo(bestMove.first, bestMove.second, O);
    for (std::pair<int, int> move: currentState.getPossibleMoves())
    {
        currentState.set(move.first, move.second, O);
        int currentValue{currentState.evaluate()};
        currentState.undo(move.first, move.second, O);
        if (currentValue < bestValue)
        {
            bestMove = move;
        }
        bestValue = std::min(bestValue, currentValue);
    }
    currentState.place(bestMove.first, bestMove.second, bot);
    currentPlayer = human;
}

int Game::minimax(Player player)
{
    if (currentState.isTerminal())
    {
        return currentState.evaluate();
    }
    int value;
    if (player == human)
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

