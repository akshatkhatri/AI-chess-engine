#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "chessboard.h"
#include<vector>
#include<unordered_map>

bool check_piece_legality_and_move(std::vector<std::vector<char>> &chess_board, char piece, const std::string &move_start, const std::string move_dest);
bool move_is_legal(std::vector<std::vector<char>> &chess_board, const std::string &move_start, const std::string move_dest, char player_color);
void start_game(std::vector<std::vector<char>> &chess_board, std::unordered_map<char, std::string> &chess_pieces);

#endif