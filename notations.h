#ifndef NOTATIONS_H
#define NOTATIONS_H

#include<string>
#include<vector>
#include<unordered_map>

std::string convert_indices_to_UCI(std::string move_start, std::string move_dest); //e2e4
std::string convert_UCI_to_indices(); // 6,4|4,4
void construct_board_from_fen(std::vector<std::vector<char>> &board, std::string &fen,std::unordered_map<char, std::string> &chess_pieces,std::ofstream &outFile); // Board only contains '.' for now
void perfsuite_file_test(std::unordered_map<char, std::string> &chess_pieces);
void compare_perft_results(std::string &board_rep,char player_turn, std::string &castling_rights,std::vector<long long int>&filtered_perft_results,std::unordered_map<char, std::string> &chess_pieces, int test_count);

#endif