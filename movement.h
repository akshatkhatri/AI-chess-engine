#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "chessboard.h"
#include<vector>
#include<unordered_map>

bool check_piece_legality_and_move(std::vector<std::vector<char>> &chess_board, char piece, const std::string &player_move_start, const std::string player_move_dest, const std::string opponent_move_start, const std::string opponent_move_dest);
bool move_is_legal(std::vector<std::vector<char>> &chess_board, const std::string &player_move_start, const std::string player_move_dest, char player_color, const std::string opponent_move_start, const std::string opponent_move_dest);
void start_game(std::vector<std::vector<char>> &chess_board, std::unordered_map<char, std::string> &chess_pieces,char ai_color);

#endif