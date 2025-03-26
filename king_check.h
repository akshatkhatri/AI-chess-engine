#ifndef KING_CHECK_H
#define KING_CHECK_H
#include<vector>

bool is_legal_after_move(std::vector<std::vector<char>> &chess_board, int start_row, int start_col, int end_row, int end_col, char player_color);
bool king_in_check(std::vector<std::vector<char>> &chess_board, char turn_color);
bool knight_attack(int i, int j, char king, std::vector<std::vector<char>> &board);
bool rook_queen_attack(int i, int j, char king, std::vector<std::vector<char>> &board);
bool bishop_queen_attack(int i, int j, char king, std::vector<std::vector<char>> &board);
bool pawn_attack(int i, int j, char king, std::vector<std::vector<char>> &board);

#endif