cmake_minimum_required(VERSION 3.29)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToe main.cpp
        State.cpp
        State.hpp
        Player.hpp
        Game.cpp
        Game.hpp
        functions.cpp
        functions.hpp
)
