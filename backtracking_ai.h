//
// Created by Sergio P. on 7/12/17.
//

#ifndef TICTACTOE_BACKTRACKING_AI_H
#define TICTACTOE_BACKTRACKING_AI_H

#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include "game_logic.h"

typedef std::map<int, long> PositionScoreMap; // {board_position : desirability score}

class TicTacToeBot {
public:
    TicTacToeBot(const int new_symbol, int wp, int lp, int tp);
    int get_move(GameBoard board);
    int get_mark();

private:
    int bot_mark;
    int win_bias, loss_bias, tie_bias;

    long determine_move_desirability(GameBoard board, int depth, int player);
    int get_best_move(PositionScoreMap & winning_outcomes);
    std::vector<int> open_positions(const GameBoard & board);
    int get_opposite_player(int symbol);
};


////////////////////////////////////////////////////////
// TicTacToeBot public
////////////////////////////////////////////////////////

TicTacToeBot::TicTacToeBot(const int new_symbol, int wp, int lp, int tp)
        : bot_mark(new_symbol), win_bias(wp), loss_bias(lp), tie_bias(tp) {}

// Looks at each open position for current move and ranks each one. Finally returns the highest scoring move.
int TicTacToeBot::get_move(GameBoard board) {
    PositionScoreMap outcome_map;
    for (const int position: open_positions(board)) {
        board[position] = bot_mark;
        outcome_map[position] = determine_move_desirability(board, 0, bot_mark);
        board[position] = NONE;
    }
    return get_best_move(outcome_map);
}

int TicTacToeBot::get_mark() {
    return bot_mark;
}


////////////////////////////////////////////////////////
// TicTacToeBot privates
////////////////////////////////////////////////////////

/* Recursively looks ahead to the end of the game and scores this permutations desirability.
     Wins and ties increase the score. Losses reduce score using a negative multiplier.
     An immediate win grants the move a really high score so that it chosen above others.
     Changing the bias multipliers affects the way the AI plays. */
long TicTacToeBot::determine_move_desirability(GameBoard board, int depth, int player) {
    if (player_has_won(board, player)) {
        if (player == bot_mark)
            return (depth == 0) ? 100000 : ((BOARD_SIZE * BOARD_SIZE) - depth) * win_bias;

        return ((BOARD_SIZE * BOARD_SIZE) - depth) * loss_bias;
    }

    else if (is_board_full(board))
        return ((BOARD_SIZE * BOARD_SIZE) - depth) * tie_bias;

    player = get_opposite_player(player);
    long position_score = 0;

    std::vector<int> choices = open_positions(board);
    for (const int position : choices) {
        board[position] = player;
        position_score += determine_move_desirability(board, depth+1, player);
        board[position] = NONE;
    }
    return position_score;
}

// Determines the highest scoring move and returns the board position associated with it.
int TicTacToeBot::get_best_move(PositionScoreMap & scores) {
    long highest_score = std::numeric_limits<int>::min(); // higher score is better
    int position = -1;

    for (const auto pos_score : scores) {
        if (pos_score.second > highest_score) {
            highest_score = pos_score.second;
            position = pos_score.first;
        }
    }
    return position;
}

// Returns a vector containing the board positions that are available.
std::vector<int> TicTacToeBot::open_positions(const GameBoard &board) {
    std::vector<int> result;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (board[i] == NONE)
            result.push_back(i);
    }
    return result;
}

int TicTacToeBot::get_opposite_player(int symbol) {
    return (symbol == EX) ? CIRCLE : EX;
}

#endif //TICTACTOE_BACKTRACKING_AI_H