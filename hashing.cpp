#include "hashing.h"
#include <iostream>

uint64_t generateRandom64()
{
    static std::mt19937_64 rng(123456);                  // A machine that gives random bits with fixed seed for reproducability
    static std::uniform_int_distribution<uint64_t> dist; // Tells how to use those bits
    return dist(rng);
}

void initialize_hashes(uint64_t board_piece_hash[12][8][8], uint64_t castling_rights_hash[16], uint64_t en_passant_rights_hash[8], uint64_t side_to_move_hash[1])
{
    for (int i = 0; i < 12; i++) // Initializing Board_Piece_Hash
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                board_piece_hash[i][j][k] = generateRandom64();
            }
        }
    }

    for (int i = 0; i < 16; i++) // Initializes Castling Rights
    {
        castling_rights_hash[i] = generateRandom64();
    }

    for (int i = 0; i < 8; i++) // Initializes EN-Passant Hash
    {
        en_passant_rights_hash[i] = generateRandom64();
    }

    side_to_move_hash[0] = generateRandom64(); // Whether its black to move or not
}

int piece_to_index(char piece)
{
    switch (piece)
    {
    case 'P':
        return 0;
    case 'N':
        return 1;
    case 'B':
        return 2;
    case 'R':
        return 3;
    case 'Q':
        return 4;
    case 'K':
        return 5;
    case 'p':
        return 6;
    case 'n':
        return 7;
    case 'b':
        return 8;
    case 'r':
        return 9;
    case 'q':
        return 10;
    case 'k':
        return 11;
    default:
        return -1;
    }
}

void maybe_add_en_passant_hash(uint64_t &hash,uint64_t en_passant_rights_hash[8],const std::vector<std::vector<char>> &board,int opp_move_start_i, int opp_move_start_j,int opp_move_dest_i, int opp_move_dest_j,char player_color)
{
    if(opp_move_start_i != -1) // Ensures position is not Starting Position
    {

        char last_piece = board[opp_move_dest_i][opp_move_dest_j];
        
        // Only care about 2-step pawn move by the opponent
        bool is_two_step_pawn_move =
        (last_piece == 'p' && opp_move_start_i == 6 && opp_move_dest_i == 4) ||
        (last_piece == 'P' && opp_move_start_i == 1 && opp_move_dest_i == 3);
        
        if (!is_two_step_pawn_move)
        return;
        
        int file = opp_move_dest_j;
        int rank = opp_move_dest_i;
        
        // Now check if current player has pawn adjacent to that file
        bool adjacent_pawn_can_capture = false;
        
        if (player_color == 'W')
        {
            if (file > 0 && board[rank][file - 1] == 'P')
            adjacent_pawn_can_capture = true;
            if (file < 7 && board[rank][file + 1] == 'P')
            adjacent_pawn_can_capture = true;
        }
        else if (player_color == 'B')
        {
            if (file > 0 && board[rank][file - 1] == 'p')
            adjacent_pawn_can_capture = true;
            if (file < 7 && board[rank][file + 1] == 'p')
            adjacent_pawn_can_capture = true;
        }
        
        if (adjacent_pawn_can_capture)
        {
            hash ^= en_passant_rights_hash[file];
        }
    }
}

uint64_t generate_hash_for_position(uint64_t board_piece_hash[12][8][8], uint64_t castling_rights_hash[4], uint64_t en_passant_rights_hash[8], uint64_t side_to_move_hash[1], std::vector<std::vector<char>> &board, char player_color, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, bool white_king_moved, bool white_king_side_rook_moved, bool white_queen_side_rook_moved, bool black_king_moved, bool black_king_side_rook_moved, bool black_queen_side_rook_moved)
{
    uint64_t hash = 0;

    for (int i = 0; i < board.size(); i++) // Assigns Hash to Each Piece
    {
        for (int j = 0; j < board.size(); j++)
        {
            int idx = piece_to_index(board[i][j]);
            if (idx != -1)
            {
                hash ^= board_piece_hash[idx][i][j];
            }
        }
    }

    int castling_index = 0; // Handles Castling Rights updates
    if (!white_king_moved && !white_king_side_rook_moved)
        castling_index |= 1;
    if (!white_king_moved && !white_queen_side_rook_moved)
        castling_index |= 2;
    if (!black_king_moved && !black_king_side_rook_moved)
        castling_index |= 4;
    if (!black_king_moved && !black_queen_side_rook_moved)
        castling_index |= 8;

    hash ^= castling_rights_hash[castling_index];

    //Handles En-Passant Hashing
    maybe_add_en_passant_hash(hash,en_passant_rights_hash,board,opp_move_start_i,opp_move_start_j,opp_move_dest_i,opp_move_dest_j,player_color);

    //Handles Player Turn Hashing
    if(player_color == 'B')
        hash ^= side_to_move_hash[0];

    return hash;

}