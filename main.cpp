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
#include <sstream>
#include<climits>

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

    std::vector<std::vector<char>> test_board_1 = {
        {'r', 'n', 'b', '.', 'k', 'b', 'n', 'r'}, // 0
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // 1
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 2
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 3
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 4
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 5
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 6
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // 7
    };

    std::vector<std::vector<char>> test_board_2 = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // 0
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // 1
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 2
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 3
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 4
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 5
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 6
        {'R', 'N', 'B', '.', 'K', 'B', 'N', 'R'}  // 7
    };

    std::unordered_map<char, std::string> chess_pieces = {
        {'p', "♙"}, {'P', "♟"}, {'r', "♖"}, {'R', "♜"}, {'n', "♘"}, {'N', "♞"}, {'b', "♗"}, {'B', "♝"}, {'q', "♕"}, {'Q', "♛"}, {'k', "♔"}, {'K', "♚"}};

    std::vector<std::vector<char>> board(8, std::vector<char>(8, '.')); // Initialized Empty Board

    // std::string fen = "2kr3r/1pp2ppp/p1p1b3/4P3/4P3/2N1P3/PPP3PP/R1K4R w - - 1 13";
    // construct_board_from_fen(board, fen);
    // bool t = true;
    // // std::cout<<minimax_driver(4,board,-1,-1,-1,-1,'W')<<std::endl;
    // std::cout << print_all_legal_moves_for_a_position(board, 'W', chess_pieces) << std::endl;
    // std::vector<std::string> gen_moves = generate_legal_moves_for_a_piece(board, 'W', 7, 2, -1, -1, -1, -1, t, t, t, t, t, t);
    // for (int k = 0; k < gen_moves.size(); k++)
    // {
    //     std::cout << gen_moves[k] << std::endl;
    // }
    // std::cout<<convert_indices_to_UCI("7,2","7,6")<<std::endl;
    // Below Code Initializes A zobrish Hashing methodology

    // uint64_t board_piece_hash[12][8][8];
    // uint64_t castling_rights_hash[16];
    // uint64_t en_passant_rights_hash[8];
    // uint64_t side_to_move_hash[1];

    // initialize_hashes(board_piece_hash,castling_rights_hash,en_passant_rights_hash,side_to_move_hash); // Fills Up the Hashes Values
    // uint64_t sample_test_hash = generate_hash_for_position(board_piece_hash,castling_rights_hash,en_passant_rights_hash,side_to_move_hash,chess_board,'W',-1,-1,-1,-1,false,false,false,false,false,false);
    // std::cout<<sample_test_hash<<std::endl;

    // int eval_1 = static_evaluate(test_board_1, 'W', 'W');
    // std::cout << eval_1 << std::endl;

    // int eval_2 = static_evaluate(test_board_2, 'B', 'B');
    // std::cout << eval_2 << std::endl;

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

    // Update Turn as the Last Parameter
    //  perft_divide(target_depth,test_board,1,1,5,3,5,ep_moves,'w'); // Changes to parameter 4 to 7 should be removed and kept to -1 always

    // std::cout << "Total ep moves at depth " << target_depth << ": " << ep_moves << std::endl;

    /*

    CAUTION !! CAUTION !! CAUTION !!
    UNCOMMENT THE BELOW LINES TO START THE GAME

    */
    // print_welcome_message();
    // start_game(chess_board, chess_pieces,'W'); // Uncomment this line to Start The Game and set test_board to chess_board and Ai_color to 'W' for white and 'B' For black any other for P V/s P

    // std::cout<<convert_UCI_to_indices("e2e4")<<std::endl;

    bool _white_king_moved = false;
    bool _white_king_side_rook_moved = false;
    bool _white_queen_side_rook_moved = false;
    bool _black_king_moved = false;
    bool _black_king_side_rook_moved = false;
    bool _black_queen_side_rook_moved = false;

    std::string line;
    int move_count = 0;
    std::string prev_move_start;
    std::string prev_move_end;

    // std::cout << "UCI START" << std::endl;

    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        int turn_count = 1;

        if (token == "uci")
        {
            std::cout << "id name MyCoolBot\nid author Akshat\nuciok" << std::endl;
        }
        else if (token == "isready")
        {
            std::cout << "readyok" << std::endl;
        }
        else if (token == "quit")
        {
            break;
        }
        else if (token == "position")
        {
            std::string sub;
            iss >> sub;

            if (sub == "startpos")
            {
                // reset to standard starting positiion
                board = chess_board;
            }
            else if (sub == "fen")
            {
                std::string fen = "", temp;
                int parts = 6;
                while (parts-- && iss >> temp)
                    fen += temp + " ";
                construct_board_from_fen(board, fen);

                std::istringstream fen_stream(fen);
                std::string piece_placement, active_color, castling_rights, en_passant, halfmove, fullmove;
                fen_stream >> piece_placement >> active_color >> castling_rights >> en_passant >> halfmove >> fullmove;

                int turn_count = (active_color == "w") ? 1 : 2;

                _white_king_moved = true;
                _white_king_side_rook_moved = true;
                _white_queen_side_rook_moved = true;
                _black_king_moved = true;
                _black_king_side_rook_moved = true;
                _black_queen_side_rook_moved = true;

                for (char c : castling_rights)
                {
                    switch (c)
                    {
                    case 'K':
                        _white_king_moved = false;
                        _white_king_side_rook_moved = false;
                        break;
                    case 'Q':
                        _white_king_moved = false;
                        _white_queen_side_rook_moved = false;
                        break;
                    case 'k':
                        _black_king_moved = false;
                        _black_king_side_rook_moved = false;
                        break;
                    case 'q':
                        _black_king_moved = false;
                        _black_queen_side_rook_moved = false;
                        break;
                    }
                }
            }
            std::string line_after_moves;
            std::size_t moves_pos = line.find("moves");
            // std::cout<<"here1"<<std::endl;
            if (moves_pos != std::string::npos)
            {
                // std::cout<<"here 2"<<std::endl;
                line_after_moves = line.substr(moves_pos + 6); // Skip "moves "
                std::istringstream move_stream(line_after_moves);
                std::string move;

                while (move_stream >> move)
                {
                    std::string converted_move = convert_UCI_to_indices(move);
                    // std::cout << "UCI Move: " << move << ", Converted: " << converted_move << std::endl;
                    std::string curr_move_start = converted_move.substr(0, 3);
                    std::string curr_move_end = converted_move.substr(4);

                    
                    if (turn_count % 2 == 1)
                    {
                        move_is_legal(board, curr_move_start, curr_move_end, 'W', prev_move_start, prev_move_end, _white_king_moved, _white_king_side_rook_moved, _white_queen_side_rook_moved);
                    }
                    else
                    {
                        move_is_legal(board, curr_move_start, curr_move_end, 'B', prev_move_start, prev_move_end, _black_king_moved, _black_king_side_rook_moved, _black_queen_side_rook_moved);
                    }

                    prev_move_start = curr_move_start;
                    prev_move_end = curr_move_end;

                    ++move_count;
                    turn_count++;
                }
            }
            std::cout<<"Set"<<std::endl;
        }

        else if (token == "go")
        {
            // display_board(board, chess_pieces);
            int fixed_depth = 4;
            // std::cout << move_count << std::endl
            //           << std::flush;

            int prev_i = -1, prev_j = -1, dest_i = -1, dest_j = -1;

            if (prev_move_start.size() == 3 && prev_move_end.size() == 3)
            {
                prev_i = prev_move_start[0] - '0';
                prev_j = prev_move_start[2] - '0';
                dest_i = prev_move_end[0] - '0';
                dest_j = prev_move_end[2] - '0';
            }

            std::string best_move = minimax_driver(fixed_depth, board, prev_i, prev_j, dest_i, dest_j, (move_count % 2 == 0) ? 'W' : 'B',_white_king_moved,_white_king_side_rook_moved,_white_queen_side_rook_moved,_black_king_moved,_black_king_side_rook_moved,_black_queen_side_rook_moved);

            std::string best_UCI_move = convert_indices_to_UCI(best_move.substr(0, 3), best_move.substr(4));
            std::cout << "bestmove " << best_UCI_move << std::endl;

            move_count = 0;
        }

        // move_count = 0;
    }

    return 0;
}
// position startpos moves e2e4 e7e5 b1c3 b8c6 g1f3 d7d5 e4d5 c6d4

// position startpos moves e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5 a7a6 b5c6 d7c6 f3e5 f8d6 d2d4 d6e5 d4e5 d8d1 e1d1 f6g4 c1e3 c8e6

// position startpos moves e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5 a7a6 b5c6 d7c6 f3e5 f8d6 d2d4 d6e5 d4e5 d8d1 e1d1 f6g4 c1e3 c8e6 d1c1 g4e3 f2e3 e8c8
