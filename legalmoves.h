#ifndef LEGALMOVES_H
#define LEGALMOVES_H

#include<vector>
#include<string>
#include<unordered_map>

extern unsigned long long int moves;

void sample_perft_test(int depth, std::vector<std::vector<char>> &chess_board, int curr_depth, unsigned long long int &moves);
std::vector<std::string> generate_legal_moves_for_a_piece(std::vector<std::vector<char>> &chess_board, char player_color, int row, int col);
int print_all_legal_moves_for_a_position(std::vector<std::vector<char>> &chess_board, char player_color, std::unordered_map<char, std::string> &chess_pieces);

#endif
