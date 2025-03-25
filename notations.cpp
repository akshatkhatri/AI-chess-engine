#include "notations.h"
#include <iostream>
#include <string>

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
