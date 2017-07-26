#include <iostream>
#include "game_logic.h"

//#include "simple_ai.h" //Only one can be active at a time
#include "backtracking_ai.h"

void display_welcome_message() {
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
    std::cout << "                      Tic Tac Toe"                        << std::endl;
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
}

void display_goodbye_message() {
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
    std::cout << "                      Game ended."                        << std::endl;
    std::cout << "////////////////////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
}

int select_mark(const std::string prompt) {
    while (true)
    {
        try {
            char mark;
            std::cout << prompt;
            std::cin >> mark;
            switch (mark) {
                case 'O':
                    return CIRCLE;
                case 'o':
                    return CIRCLE;
                case 'X':
                    return EX;
                case 'x':
                    return EX;
                default:
                    throw std::runtime_error("Incorrect mark selected try again.");
            }
        }
        catch (std::runtime_error &er) {
            std::cout << er.what() << std::endl; }
    }
}

GameBoard new_board() {
    GameBoard result(9);
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
            result[i] = 0;
    }
    return result;
}

void display_board(const GameBoard & b) {
    std::cout << "\n";
    int position = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++, position++) {
            if (b[position] == NONE)
                std::cout << ". ";
            else if (b[position] == CIRCLE)
                std::cout << "O ";
            else
                std::cout << "X ";
        }
        std::cout << std::endl;
    }
}

void display_turn(const int player) {
    std::cout << "\n";
    if (player == CIRCLE)
        std::cout << "O's turn." << std::endl;
    else
        std::cout << "X's turn." << std::endl;
}

void display_winner(const int player) {
    if (player == NONE)
        std::cout << "Tied game!" << std::endl;

    else if (player == CIRCLE)
        std::cout << "Winner is O." << std::endl;

    else
        std::cout << "Winner is X." << std::endl;
}

TicTacToeBot initialize_bot(int mark, int who_first) {
    if (mark == who_first)
        return TicTacToeBot(mark, 2,-1,1); //remove the three additional numbers if using simple_ai

    return TicTacToeBot(mark, 1,-1,1);
}

BoardPosition get_move(const GameBoard & board, const int current_player, TicTacToeBot & bot) {
    BoardPosition move;
    if (current_player == bot.get_mark())
        move = bot.get_move(board);

    else {
        std::cout << "Enter box number: ";
        std::cin >> move;
        move--;
    }

    return move;
}

bool prompt_to_play_again() {
    std::string response;
    std::cout << "\n";
    std::cout << "Do you want to play again? (yes or no): ";
    std::cin >> response;

    return !(response == "no" or response == "n" or response == "N");
}

void run_game(const int player_one, const int player_two, const int who_first) {
    GameBoard board = new_board();
    int current_player = who_first;
    bool winner_exists = false;
    bool board_is_full = false;
    TicTacToeBot bot = initialize_bot(player_two, who_first);

    while (true) {
        display_board(board);
        display_turn(current_player);

        BoardPosition player_move = get_move(board, current_player, bot);

        make_move(board, player_move, current_player);

        winner_exists = player_has_won(board, current_player);
        board_is_full = is_board_full(board);
        current_player = determine_next_player(winner_exists, board_is_full, current_player);

        if (winner_exists or board_is_full)
            break;
    }
    display_board(board);
    display_winner(current_player);
}

int main() {

    display_welcome_message();
    int player_one = select_mark("Player 1 select your mark, (X or O): ");
    int player_two = (player_one == CIRCLE) ? EX : CIRCLE;
    int who_first = select_mark("Who goes first? (X or O): ");
    bool play_again = true;

    while (play_again) {
        run_game(player_one, player_two, who_first);
        play_again = prompt_to_play_again();
        who_first = (who_first == CIRCLE) ? EX : CIRCLE;

    }

    display_goodbye_message();
    return 0;
}