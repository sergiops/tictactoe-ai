//
// Created by Sergio P. on 7/9/17.
//

#ifndef TICTACTOE_SIMPLE_AI_H
#define TICTACTOE_SIMPLE_AI_H

#include <iostream>
#include "game_logic.h"

class TicTacToeBot {
public:
    TicTacToeBot(const int new_symbol);
    int get_move(const GameBoard & board);
    int get_mark();

private:
    int symbol;
    int find_winning_move(const GameBoard & board);
    int find_blocking_move(const GameBoard & board);
    int take_center(const GameBoard & board);
    int find_open_corner(const GameBoard & board);
    int find_open_side(const GameBoard & board);

    int find_possible_move(const GameBoard & board, const int target_symbol,
                                        const int & pos1,
                                        const int & pos2,
                                        const int & pos3);

    int get_opposite_player();
};


///////////////////////////////////////////////////////////////////////
// Public methods
///////////////////////////////////////////////////////////////////////

TicTacToeBot::TicTacToeBot(const int new_symbol)
:symbol(new_symbol) {}

int TicTacToeBot::get_move(const GameBoard & board) {

    int move = find_winning_move(board);
    if (move != -1)
        return move;

    move = find_blocking_move(board);
    if (move != -1)
        return move;

    move = find_open_corner(board);
    if (move != -1)
        return move;

    move = take_center(board);
    if (move != -1)
        return move;

    return find_open_side(board);
}

int TicTacToeBot::get_mark() {
    return symbol;
}


///////////////////////////////////////////////////////////////////////
// Private methods
///////////////////////////////////////////////////////////////////////

int TicTacToeBot::find_winning_move(const GameBoard & board) {
    for (const auto & positions : ALL_WINNING_SEQUENCES) {
        int possible_win = find_possible_move(board, symbol,
                                                        positions[0],
                                                        positions[1],
                                                        positions[2]);
        if (possible_win != -1)
            return possible_win;
    }
    return -1; // No winning move possible.
}

int TicTacToeBot::find_blocking_move(const GameBoard & board) {
    for (const auto & positions : ALL_WINNING_SEQUENCES) {
        int possible_block = find_possible_move(board, get_opposite_player(),
                                                          positions[0],
                                                          positions[1],
                                                          positions[2]);
        if (possible_block != -1)
            return possible_block;
    }
    return -1; // Nothing to block.
}

int TicTacToeBot::take_center(const GameBoard &board) {
    if (board[4] == NONE)
        return 4;

    return -1; // Center taken.
}

int TicTacToeBot::find_open_corner(const GameBoard &board) {
    if (board[0] == NONE)
        return 0;
    else if (board[2] == NONE)
        return 2;
    else if (board[6] == NONE)
        return 6;
    else if (board[8] == NONE)
        return 8;

    return -1; // Corners taken.
}

int TicTacToeBot::find_open_side(const GameBoard & board) {
    if (board[1] == NONE)
        return 1;
    else if (board[3] == NONE)
        return 3;
    else if (board[5] == NONE)
        return 5;
    else if (board[7] == NONE)
        return 7;

    std::cerr << "WARNING: RETURNING -1 FORM FIND_OTHER_MOVE" << std::endl;
    return -1;
}

// Scans one winning sequence and determines a possible move to either win or
// prevent opposing player from winning.
int TicTacToeBot::find_possible_move(const GameBoard & board, const int target_symbol,
                                               const int & pos1,
                                               const int & pos2,
                                               const int & pos3) {

    if (board[pos1] == target_symbol and
            board[pos2]== target_symbol and
            board[pos3] == NONE)
        return pos3;

    if (board[pos1] == target_symbol and
            board[pos3] == target_symbol and
            board[pos2] == NONE)
        return pos2;

    if (board[pos2] == target_symbol and
            board[pos3] == target_symbol and
            board[pos1] == NONE)
        return pos1;

    return -1; // No valid move possible.

}

int TicTacToeBot::get_opposite_player() {
    if (symbol == CIRCLE)
        return EX;

    return CIRCLE;
}

#endif //TICTACTOE_SIMPLE_AI_H