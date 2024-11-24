#ifndef TICTACTOE_PLAYER_HPP
#define TICTACTOE_PLAYER_HPP

enum Player
{
    X = 1,
    O = -1,
    Empty = 0
};

inline std::ostream& operator<<(std::ostream& os, const Player& player)
{
    switch (player)
    {
        case X:
            os << " X ";
            break;
        case O:
            os << " O ";
            break;
        default:
            os << " . ";
            break;
    }
    return os;
}

#endif //TICTACTOE_PLAYER_HPP
