#include <iostream>
#include "chessboard.h"
#include "movement.h"
#include "king_check.h"
#include "legalmoves.h"
#include "notations.h"
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

    std::vector<std::vector<char>> test_board = {
        {'.', '.', '.', '.', '.', '.', '.', '.'},  // Rank 8
        {'.', '.', '.', '.', '.', '.', '.', '.'},  // Rank 7
        {'.', 'k', '.', '.', '.', '.', '.', '.'},  // Rank 6
        {'.', '.', 'b', '.', '.', '.', '.', '.'},  // Rank 5
        {'.', '.', 'p', 'P', '.', '.', '.', '.'},  // Rank 4
        {'.', '.', '.', '.', '.', '.', '.', '.'},  // Rank 3
        {'.', '.', '.', '.', '.', 'K', '.', '.'},  // Rank 2
        {'.', '.', '.', '.', '.', '.', '.', '.'}   // Rank 1
    };
    

    std::unordered_map<char, std::string> chess_pieces = {
        {'p', "♙"}, {'P', "♟"}, {'r', "♖"}, {'R', "♜"}, {'n', "♘"}, {'N', "♞"}, {'b', "♗"}, {'B', "♝"}, {'q', "♕"}, {'Q', "♛"}, {'k', "♔"}, {'K', "♚"}};

    // unsigned long long int moves = 0;
    // int ep_moves = 0;
    // long long int castling_moves = 0;
    // long long int promotion_moves = 0;
    // int depth;

    // std::cout << "Enter Depth\n";
    // std::cin >> depth;

    // sample_perft_test(depth, test_board, 1, moves, 6, 3, 4, 3, ep_moves, 'b', castling_moves, promotion_moves); // Running for test_board not chess_board and change color accordingly
    
    // std::cout << "Perft for depth " << depth << " is" << moves << std::endl;
    // std::cout << "En-passant moves were " << ep_moves << std::endl;
    // std::cout << "Castling moves were " << castling_moves << std::endl;
    // std::cout << "Promotion moves were " << promotion_moves << std::endl;

    perfsuite_file_test(chess_pieces);
    std::cout<<"Tests Done"<<std::endl;
    getchar();

    // int target_depth = 2;
    // unsigned long long int total_moves = 0;
    // int ep_moves = 0;
    // long long int castling_moves = 0;
    // // sample_perft_test(target_depth,test_board, 1,total_moves, -1, -1, -1, -1, ep_moves, 'b',castling_moves);

    //Update Turn as the Last Parameter
    // perft_divide(target_depth,test_board,1,1,5,3,5,ep_moves,'w'); // Changes to parameter 4 to 7 should be removed and kept to -1 always

    // std::cout << "Total ep moves at depth " << target_depth << ": " << ep_moves << std::endl;

    /*

    CAUTION !! CAUTION !! CAUTION !!
    UNCOMMENT THE BELOW LINES TO START THE GAME

    */
    //    print_welcome_message();
    // start_game(test_board, chess_pieces); // Uncomment this line to Start The Game and set test_board to chess_board

    return 0;
}
