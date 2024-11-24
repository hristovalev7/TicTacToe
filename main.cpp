#include "Game.hpp"
#include <chrono>

int main()
{
//    auto start = std::chrono::high_resolution_clock::now();
//    Game game;
//    int test = game.minimax();
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = end - start;
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    Game game;
    game.start();
    return 0;
}
