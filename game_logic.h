//
// Created by Sergio P. on 7/2/17.
//

#ifndef TICTACTOE_GAME_LOGIC_H
#define TICTACTOE_GAME_LOGIC_H

#include <vector>

typedef std::vector<int> GameBoard;
typedef std::vector<int> WinSequence;
typedef std::vector<WinSequence> SequenceVector;

const int NONE = 0;
const int CIRCLE = 1;
const int EX = 2;

const int BOARD_SIZE = 3;

const SequenceVector ALL_WINNING_SEQUENCES ({
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},

        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},

        {0, 4, 8},
        {6, 4, 2}
});

void make_move(GameBoard & b, const int move, const int player) {
    b[move] = player;
}

bool player_has_won(const GameBoard & b, const int player) {
    for (const WinSequence & positions : ALL_WINNING_SEQUENCES) {
        if (b[positions[0]] == player and b[positions[1]] == player and b[positions[2]] == player)
            return true;
    }
    return false;
}

bool is_board_full(const GameBoard & b) {
    for (int position = 0; position < BOARD_SIZE*BOARD_SIZE; position++) {
        if (b[position] == NONE)
            return false;
    }
    return true;
}

int determine_next_player(const bool winner_exists, const bool full, const int player) {
    if (full and !winner_exists)
        return NONE;

    else if (winner_exists)
        return player;

    if (player == CIRCLE)
        return EX;

    return CIRCLE;
}

#endif //TICTACTOE_GAME_LOGIC_H