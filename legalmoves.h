#ifndef LEGALMOVES_H
#define LEGALMOVES_H

#include <vector>
#include <string>
#include <unordered_map>

extern unsigned long long int moves;

void set_castling_rights(const std::string &castling_rights);
void sample_perft_test(int depth, std::vector<std::vector<char>> &chess_board, int curr_depth, unsigned long long int &moves, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, int &ep_moves, char player_turn, long long int &castling_moves, long long int &promotion_moves);
std::vector<std::string> generate_legal_moves_for_a_piece(std::vector<std::vector<char>> &chess_board, char player_color, int row, int col, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, bool &white_king_moved, bool &white_king_side_rook_moved, bool &white_queen_side_rook_moved, bool &black_king_moved, bool &black_king_side_rook_moved, bool &black_queen_side_rook_moved);
void perft_divide(int target_depth, std::vector<std::vector<char>> &chess_board, int curr_depth, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, int &ep_moves, char player_turn);
bool is_legal_move_available(std::vector<std::vector<char>> &chess_board, char current_turn, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j);
bool is_checkmate(std::vector<std::vector<char>> &chess_board, char current_turn, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j);
bool is_stalemate(std::vector<std::vector<char>> &chess_board, char current_turn, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j);
int print_all_legal_moves_for_a_position(std::vector<std::vector<char>> &chess_board, char player_color, std::unordered_map<char, std::string> &chess_pieces);

#endif
