cmake_minimum_required(VERSION 3.6)
project(tictactoe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        game_logic.h
        simple_ai.h
        backtracking_ai.h
        test_backtrack_ai.cpp)

add_executable(tictactoe ${SOURCE_FILES})