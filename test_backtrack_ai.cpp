////
//// Created by Sergio P. on 7/19/17.
////
//
//
//#include <iostream>
//#include <vector>
//#include "game_logic.h"
//#include "backtracking_ai.h"
//
//
//const std::vector<int> board = {2,2,1,0,1,0,2,0,0};
//
//void display_board(const GameBoard & b) {
//    std::cout << "\n";
//    int position = 0;
//    for(int i = 0; i < BOARD_SIZE; i++)
//    {
//        for(int j = 0; j < BOARD_SIZE; j++, position++) {
//            if (b[position] == NONE)
//                std::cout << ". ";
//            else if (b[position] == CIRCLE)
//                std::cout << "O ";
//            else
//                std::cout << "X ";
//        }
//        std::cout << std::endl;
//    }
//}
//
//int main() {
//
//    TicTacToeBot bot(CIRCLE);
//    display_board(board);
//    int move = bot.get_move(board);
//    std::cout << "move = " << move << std::endl;
//
//    return 0;
//}