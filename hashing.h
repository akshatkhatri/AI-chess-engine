#ifndef HASHING_H
#define HASHING_H

#include <random>
#include <cstdint>
#include <vector>

uint64_t generateRandom64();
void initialize_hashes(uint64_t board_piece_hash[12][8][8], uint64_t castling_rights_hash[4], uint64_t en_passant_rights_hash[8], uint64_t side_to_move_hash[1]);
uint64_t generate_hash_for_position(uint64_t board_piece_hash[12][8][8], uint64_t castling_rights_hash[4], uint64_t en_passant_rights_hash[8], uint64_t side_to_move_hash[1], std::vector<std::vector<char>> &board,char player_color, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, bool white_king_moved, bool white_king_side_rook_moved, bool white_queen_side_rook_moved, bool black_king_moved, bool black_king_side_rook_moved, bool black_queen_side_rook_moved);
int piece_to_index(char piece);

#endif
