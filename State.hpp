#ifndef TICTACTOE_STATE_HPP
#define TICTACTOE_STATE_HPP

#include <iostream>
#include <vector>
#include <set>
#include "Player.hpp"

#define BOARD_SIZE 3
#define DELIM '|'

class State
{
private:
    std::vector<std::vector<Player>> board;
    std::vector<int> columns;
    std::vector<int> rows;
    std::vector<int> diagonals;
    std::set<std::pair<int, int>> possibleMoves;

public:
    State();

    void place(int x, int y, Player player);

    [[nodiscard]] bool xWins() const;

    [[nodiscard]] bool oWins() const;

    [[nodiscard]] bool isTerminal() const;

    [[nodiscard]] std::set<std::pair<int, int>> getPossibleMoves() const;

    void print() const;

    [[nodiscard]] int getDepth() const;

    [[nodiscard]] int evaluate() const;

    void set(int x, int y, Player player);

    void undo(int x, int y, Player player);

    bool isFree(int x, int y) const;

private:
    void updateDiagonals(int x, int y, Player player);
};

#endif //TICTACTOE_STATE_HPP
