#include "notations.h"
#include "legalmoves.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

void construct_board_from_fen(std::vector<std::vector<char>> &board, std::string &fen, std::unordered_map<char, std::string> &chess_pieces,std::ofstream &outFile)
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
            outFile << (board[i][j] != '.' ? chess_pieces[board[i][j]] : ".") << " ";
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
    while (getline(fen_file, line))
    {
        std::string board_rep;
        char player_turn;
        std::string castling_rights;
        std::vector<int> filtered_perft_results;

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
                filtered_perft_results.push_back(stoi(token));
            }
        }

        // Till here we have extracted all details from the file's line
        test_count++;
        compare_perft_results(board_rep, player_turn, castling_rights, filtered_perft_results, chess_pieces, test_count);
    }
}

void compare_perft_results(std::string &board_rep, char player_turn, std::string &castling_rights, std::vector<int> &filtered_perft_results, std::unordered_map<char, std::string> &chess_pieces, int test_count)
{
    unsigned long long int moves = 0; // Stores Moves passed as reference to perft test
    int ep_moves = 0;

    std::ofstream outFile("perft_results.txt", std::ios::app);
    std::vector<std::vector<char>> chess_board(8, std::vector<char>(8, '.')); // Initialized Empty Board
    std::vector<int> my_perft_results;
    construct_board_from_fen(chess_board, board_rep, chess_pieces,outFile); // Constructs a 8 * 8 chessboard

    set_castling_rights(castling_rights);                           // Initialized Castling Rights in Move generator

    for (int depth = 1; depth <= 5; depth++)
    {
        sample_perft_test(depth, chess_board, 1, moves, -1, -1, -1, -1, ep_moves, player_turn);
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

        std::cout << "Test #"<< test_count<<" ✅ Complete" << std::endl;

        outFile << "Test #"<< test_count<<" ✅ Complete" << std::endl;

        outFile.close(); // Close the file
    }
    else
    {
        std::cerr << "Error: Unable to open perft_results.txt for writing." << std::endl;
    }
}
