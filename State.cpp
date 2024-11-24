#include "State.hpp"

State::State()
{
    board.reserve(BOARD_SIZE);
    for (int i{0}; i < BOARD_SIZE; ++i)
    {
        board.emplace_back(BOARD_SIZE, Empty);
        for (int j{0}; j < BOARD_SIZE; ++j)
        {
            possibleMoves.emplace(i, j);
        }
    }
    columns.resize(BOARD_SIZE);
    rows.resize(BOARD_SIZE);
    diagonals.resize(2);
}

void State::place(int x, int y, Player player)
{
    board[x][y] = player;
    rows[x] += player;
    columns[y] += player;
    updateDiagonals(x, y, player);
    possibleMoves.erase({x, y});
    print();
}

bool State::xWins() const
{
    return columns[0] == 3 || columns[1] == 3 || columns[2] == 3 || rows[0] == 3 || rows[1] == 3 || rows[2] == 3 || diagonals[0] == 3 || diagonals[1] == 3;
}

bool State::oWins() const
{
    bool b1{columns[0] == -3};
    bool b2{columns[1] == -3};
    bool b3{columns[2] == -3};
    bool b4{rows[0] == -3};
    bool b5{rows[1] == -3};
    bool b6{rows[2] == -3};
    bool b7{diagonals[0] == -3};
    bool b8{diagonals[1] == -3};
    return b1 || b2 || b3 || b4 || b5 || b6 || b7 || b8;
}

bool State::isTerminal() const
{
    return oWins() || xWins() || (!oWins() && !xWins() && possibleMoves.empty());
}

std::set<std::pair<int, int>> State::getPossibleMoves() const
{
    return possibleMoves;
}

void State::print() const
{
    for (int i{0}; i < BOARD_SIZE; ++i)
    {
        for (int j{0}; j < BOARD_SIZE - 1; ++j)
        {
            std::cout << board[i][j] << DELIM;
        }
        std::cout << board[i][BOARD_SIZE - 1] << '\n';
    }
}

int State::getDepth() const
{
    return 9 - static_cast<int> (possibleMoves.size());
}

int State::evaluate() const
{
    if (xWins())
    {
        return 10 - getDepth();
    }
    if (oWins())
    {
        return getDepth() - 10;
    }
    return 0;
}

void State::updateDiagonals(int x, int y, Player player)
{
    if (x + y == 2)
    {
        diagonals[1] += player;
    }
    if (x == y)
    {
        diagonals[2] += player;
    }
}

void State::set(int x, int y, Player player)
{
    board[x][y] = player;
    rows[x] += player;
    columns[y] += player;
    updateDiagonals(x, y, player);
    possibleMoves.erase({x, y});
}

void State::undo(int x, int y, Player player)
{
    board[x][y] = Empty;
    rows[x] -= player;
    columns[y] -= player;
    updateDiagonals(x, y, static_cast<Player>(-player));
    possibleMoves.emplace(x, y);
}

