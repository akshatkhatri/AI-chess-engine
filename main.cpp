#include <iostream>
#include "chessboard.h"
#include "movement.h"
#include "king_check.h"
#include <vector>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001); // Set UTF-8 encoding for Windows console
#endif

    std::vector<std::vector<char>> chess_board = {
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
        {'p', "♙"}, {'P', "♟"}, 
        {'r', "♖"}, {'R', "♜"}, 
        {'n', "♘"}, {'N', "♞"}, 
        {'b', "♗"}, {'B', "♝"}, 
        {'q', "♕"}, {'Q', "♛"}, 
        {'k', "♔"}, {'K', "♚"}
    };

    print_welcome_message();
    start_game(chess_board, chess_pieces);

    return 0;
}
