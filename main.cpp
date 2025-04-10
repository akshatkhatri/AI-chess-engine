#include <iostream>
#include "chessboard.h"
#include "movement.h"
#include "king_check.h"
#include "legalmoves.h"
#include "notations.h"
#include "hashing.h"
#include "Evaluation.h"
#include "Search.h"
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
        {'.', '.', '.', '.', '.', 'N', '.', '.'}, // 5
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 6
        {'R', 'N', 'B', 'Q', 'K', 'B', '.', 'R'}  // 7
    };

    std::vector<std::vector<char>> test_board_1 = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // 0
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // 1
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 2
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 3
        {'.', '.', '.', '.', 'P', '.', '.', '.'}, // 4
        {'.', '.', '.', '.', '.', '.', '.', 'P'}, // 5
        {'P', 'P', 'P', 'P', '.', 'P', 'P', '.'}, // 6
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // 7
    };

    std::vector<std::vector<char>> test_board_2 = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // 0
        {'p', 'p', 'p', 'p', '.', 'p', 'p', 'p'}, // 1
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 2
        {'.', '.', '.', '.', 'p', '.', '.', '.'}, // 3
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 4
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 5
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 6
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // 7
    };


    std::unordered_map<char, std::string> chess_pieces = {
        {'p', "♙"}, {'P', "♟"}, {'r', "♖"}, {'R', "♜"}, {'n', "♘"}, {'N', "♞"}, {'b', "♗"}, {'B', "♝"}, {'q', "♕"}, {'Q', "♛"}, {'k', "♔"}, {'K', "♚"}};


        //Below Code Initializes A zobrish Hashing methodology
    
    // uint64_t board_piece_hash[12][8][8];
    // uint64_t castling_rights_hash[16];
    // uint64_t en_passant_rights_hash[8];
    // uint64_t side_to_move_hash[1];

    // initialize_hashes(board_piece_hash,castling_rights_hash,en_passant_rights_hash,side_to_move_hash); // Fills Up the Hashes Values
    // uint64_t sample_test_hash = generate_hash_for_position(board_piece_hash,castling_rights_hash,en_passant_rights_hash,side_to_move_hash,chess_board,'W',-1,-1,-1,-1,false,false,false,false,false,false);
    // std::cout<<sample_test_hash<<std::endl;

    int eval_1 = static_evaluate(test_board_1,'W','W');
    std::cout<<eval_1<<std::endl;

    
    int eval_2 = static_evaluate(test_board_2,'B','B');
    std::cout<<eval_2<<std::endl;
    

    // Generates Best Move uPto a ply for a given Position
    // std::cout<<minimax_driver(5,chess_board,-1,-1,-1,-1,'W');

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

    // perfsuite_file_test(chess_pieces);
    // std::cout<<"Tests Done"<<std::endl;
    // getchar();

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
    print_welcome_message();
    start_game(chess_board, chess_pieces,'B'); // Uncomment this line to Start The Game and set test_board to chess_board and Ai_color to 'W' for white and 'B' For black any other for P V/s P

    return 0;
}
