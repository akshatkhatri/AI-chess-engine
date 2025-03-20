#include<iostream>
#include "chessboard.h"
#include "movement.h"
#include "king_check.h"
#include<windows.h>
#include<vector>
#include<unordered_map>

int main()
{
    SetConsoleOutputCP(65001);
    std::vector<std::vector<char>> chess_board = {
        //    0    1    2    3    4    5    6    7
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // 0
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // 1
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 2
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 3
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 4
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 5
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 6
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // 7
    };

    std::unordered_map<char, std::string> chess_pieces = {
        {'P', "♙"}, {'p', "♟"},  // White Pawn, Black Pawn
        {'R', "♖"}, {'r', "♜"},  // White Rook, Black Rook
        {'N', "♘"}, {'n', "♞"},  // White Knight, Black Knight
        {'B', "♗"}, {'b', "♝"},  // White Bishop, Black Bishop
        {'Q', "♕"}, {'q', "♛"},  // White Queen, Black Queen
        {'K', "♔"}, {'k', "♚"}   // White King, Black King
    };

    print_welcome_message();
    start_game(chess_board,chess_pieces);

    return 0;
}
