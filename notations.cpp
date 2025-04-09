#include "notations.h"
#include "legalmoves.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<iomanip>

std::string convert_indices_to_UCI(std::string move_start, std::string move_dest)
{
    // Code to Convert explicit indexes into UCI
    int row_index_start = move_start[0] - '0';
    int col_index_start = move_start[2] - '0';
    int row_index_dest = move_dest[0] - '0';
    int col_index_dest = move_dest[2] - '0';

    char col_start_UCI = 'A' + col_index_start; // e
    int row_start_UCI = 8 - row_index_start;    // 2

    char col_dest_UCI = 'A' + col_index_dest; // e
    int row_dest_UCI = 8 - row_index_dest;    // 4

    return col_start_UCI + std::to_string(row_start_UCI) + col_dest_UCI + std::to_string(row_dest_UCI); // e2e4
}
std::string convert_UCI_to_indices(std::string UCI_move) // e2e4 → 6,4|4,4
{
    char col_start_UCI = UCI_move[0];      // 'e'
    int row_start_UCI = UCI_move[1] - '0'; // 2
    char col_dest_UCI = UCI_move[2];       // 'e'
    int row_dest_UCI = UCI_move[3] - '0';  // 4

    int col_start_idx = col_start_UCI - 'A'; // Convert 'E' -> 4
    int row_start_idx = 8 - row_start_UCI;   // Convert 2 -> 6

    int col_dest_idx = col_dest_UCI - 'A'; // Convert 'E'-> 4
    int row_dest_idx = 8 - row_dest_UCI;   // Convert 4 -> 4

    return std::to_string(row_start_idx) + "," + std::to_string(col_start_idx) + "|" + std::to_string(row_dest_idx) + "," + std::to_string(col_dest_idx);
}

void construct_board_from_fen(std::vector<std::vector<char>> &board, std::string &fen, std::unordered_map<char, std::string> &chess_pieces, std::ofstream &outFile)
{
    int row = 0;
    int col = 0;

    for (int i = 0; i < fen.size(); i++)
    {
        if (isdigit(fen[i]))
        {
            int empty_squares = fen[i] - '0';
            for (int j = 0; j < empty_squares; j++)
            {
                board[row][col] = '.'; // Ensure it's explicitly set to '.'
                col++;
            }
        }
        else if (fen[i] == '/')
        {
            row++;
            col = 0;
        }
        else
        {
            board[row][col] = fen[i];
            col++;
        }
    }

    // Uncomment below to Print Board

    outFile << "Board Position:\n";
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            outFile << std::setw(2) << (board[i][j] != '.' ? chess_pieces[board[i][j]] : ".") << " ";
        }
        outFile << "\n";
    }
    outFile << "\n";
}

void perfsuite_file_test(std::unordered_map<char, std::string> &chess_pieces)
{
    int test_count = 0;
    std::string line;
    std::ifstream fen_file("perftsuite.epd");
    if (!fen_file) {
        std::cerr << "Error: Unable to open perftsuite.epd\n";
        return;
    }

    while (getline(fen_file, line))
    {
        // std::cout << "Read line: " << line << std::endl;  // Debug print
        std::string board_rep;
        char player_turn;
        std::string castling_rights;
        std::string en_passant_square = ""; // Default value (no en passant)
        std::vector<long long int> filtered_perft_results;

        int i = 0;
        while (i < line.size() && line[i] != ' ')
        {
            board_rep.push_back(line[i]);
            i++;
        }
        i++;
        player_turn = line[i];
        i = i + 2;

        while (i < line.size() && line[i] != ' ')
        {
            castling_rights.push_back(line[i]);
            i++;
        }
        i++;

        // Extract en passant square
        if (line[i] != '-') // If there is an en passant target square
        {
            en_passant_square += line[i];
            en_passant_square += line[i + 1]; // En passant is always two characters
            i += 2;
        }
        else
        {
            i++; // Move past '-'
        }

        while (i < line.size() && line[i] != ';')
        {
            i++;
        }
        i++;

        std::string unfiltered_perft_result = line.substr(i);
        std::stringstream ss(unfiltered_perft_result);
        std::string token;

        while (ss >> token)
        { // Read each token
            if (isdigit(token[0]))
            { // If token starts with a digit
                filtered_perft_results.push_back(std::stoll(token));
            }
        }

        // Till here we have extracted all details from the file's line
        test_count++;
        // std::cout << "Calling compare_perft_results for test #" << test_count << std::endl;
        compare_perft_results(board_rep, player_turn, castling_rights, filtered_perft_results, chess_pieces, test_count,en_passant_square);
    }
}

void compare_perft_results(std::string &board_rep, char player_turn, std::string &castling_rights, std::vector<long long int> &filtered_perft_results, std::unordered_map<char, std::string> &chess_pieces, int test_count,std::string en_passant_square)
{
    std::cout << "Processing test #" << test_count << std::endl;
    unsigned long long int moves = 0;  // Stores Moves passed as reference to perft test
    int ep_moves = 0;                  // Tracking En-passant Moves
    long long int castling_moves = 0;  // Tracking Castling Moves
    long long int promotion_moves = 0; // Tracks Pawn Promotion Moves

    std::ofstream outFile("perft_results.txt", std::ios::app);
    
    std::vector<std::vector<char>> chess_board(8, std::vector<char>(8, '.')); // Initialized Empty Board
    std::vector<long long int> my_perft_results;
    construct_board_from_fen(chess_board, board_rep, chess_pieces, outFile); // Constructs a 8 * 8 chessboard
    set_castling_rights(castling_rights); // Initialized Castling Rights in Move generator

    int opp_start_i = -1, opp_start_j = -1; // Original position of opponent's pawn
    int opp_dest_i = -1, opp_dest_j = -1;   // Final position of opponent's pawn (before capture)

    // If en passant square is valid
    if (!en_passant_square.empty())  
    {
        char file = en_passant_square[0];   // Column (a-h)
        char rank = en_passant_square[1];   // Row (1-8)

        opp_start_i = player_turn == 'w'?  (8 - (rank - '0')) - 1 : (8 - (rank - '0')) + 1;       // Convert rank to row index (0-7)
        opp_start_j = file - 'a';             // Convert file to column index (0-7)

        // The opponent's pawn originally moved **two squares forward**
        if (player_turn == 'w')  
        {
            opp_dest_i = opp_start_i + 2;  // Black pawn originally came from two rows behind
        }
        else  
        {
            opp_dest_i = opp_start_i - 2;  // White pawn originally came from two rows behind
        }
        opp_dest_j = opp_start_j;  // Same column

        // std::cout<<"opp_start_i "<<opp_start_i<<std::endl; debug lines
        // std::cout<<"opp_start_j "<<opp_start_j<<std::endl; debug lines
        // std::cout<<"opp_dest_i "<<opp_dest_i<<std::endl; debug lines
        // std::cout<<"opp_dest_i "<<opp_dest_j<<std::endl; debug lines

    }

    for (int depth = 1; depth <= 6; depth++)
    {
        sample_perft_test(depth, chess_board, 1, moves, opp_start_i,opp_start_j,opp_dest_i,opp_dest_j, ep_moves, player_turn, castling_moves, promotion_moves);
        // std::cout << "Moves after depth: "<<depth<<" " << moves << std::endl;
        my_perft_results.push_back(moves);
        moves = 0;
    }

    if (outFile.is_open()) // Writes results in a file
    {
        outFile << "Perft Results Comparison:\n";

        for (size_t i = 0; i < my_perft_results.size(); i++)
        {
            outFile << "Depth " << (i + 1) << " (Mine): " << my_perft_results[i]
                    << " | Depth " << (i + 1) << " (Original): " << filtered_perft_results[i] << std::endl;
        }

        std::cout << "Test #" << test_count << " ✅ Complete" << std::endl<<std::endl;

        outFile << "Test #" << test_count << " ✅ Complete" << std::endl;

        outFile.close(); // Close the file
    }
    else
    {
        std::cerr << "Error: Unable to open perft_results.txt for writing." << std::endl;
    }
}
