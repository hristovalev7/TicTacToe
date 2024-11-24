#include "functions.hpp"

int randomBetween(int start, int end)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(rng);
}