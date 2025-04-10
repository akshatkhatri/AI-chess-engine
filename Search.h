// TO-DO
#ifndef SEARCH_H
#define SEARCH_H

#include<vector>
#include<string>

std::string minimax_driver(int target_depth, std::vector<std::vector<char>> &chess_board,int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j,char current_turn);
int minimax(std::vector<std::vector<char>> &chess_board, int depth, int alpha, int beta, bool maximizing_player, char current_turn, char ai_color, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j);

#endif