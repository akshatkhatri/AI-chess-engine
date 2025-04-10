#include "legalmoves.h"
#include "king_check.h"
#include "notations.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// unsigned long long int moves = 0; // Move Tracker
// long long int depth2_moves = 0;
bool white_king_moved = false;
bool white_king_side_rook_moved = false;
bool white_queen_side_rook_moved = false;
bool black_king_moved = false;
bool black_king_side_rook_moved = false;
bool black_queen_side_rook_moved = false;

void set_castling_rights(const std::string &castling_rights)
{
    // Reset all castling rights
    white_king_moved = true;
    white_king_side_rook_moved = true;
    white_queen_side_rook_moved = true;
    black_king_moved = true;
    black_king_side_rook_moved = true;
    black_queen_side_rook_moved = true;

    for (char c : castling_rights)
    {
        switch (c)
        {
        case 'K':
            white_king_moved = false;
            white_king_side_rook_moved = false;
            break;
        case 'Q':
            white_king_moved = false;
            white_queen_side_rook_moved = false;
            break;
        case 'k':
            black_king_moved = false;
            black_king_side_rook_moved = false;
            break;
        case 'q':
            black_king_moved = false;
            black_queen_side_rook_moved = false;
            break;
        }
    }
}
// Function For debugging
void perft_divide(int target_depth, std::vector<std::vector<char>> &chess_board, int curr_depth, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, int &ep_moves, char player_turn)
{
    if (curr_depth > target_depth)
    {
        return;
    }

    long long int castling_moves = 0;  // Unused Variable
    long long int promotion_moves = 0; // Unused Variable

    // Backup castling rights before this move
    bool wkm = white_king_moved;
    bool wksrm = white_king_side_rook_moved;
    bool wqsrm = white_queen_side_rook_moved;
    bool bkm = black_king_moved;
    bool bksrm = black_king_side_rook_moved;
    bool bqsrm = black_queen_side_rook_moved;

    unsigned long long total_positions = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char curr_square = chess_board[i][j];
            char current_turn = (player_turn == 'w') ? 'W' : 'B';

            if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
            {
                continue;
            }

            std::vector<std::string> piece_moves = generate_legal_moves_for_a_piece(chess_board, current_turn, i, j, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j, white_king_moved, white_king_side_rook_moved, white_queen_side_rook_moved, black_king_moved, black_king_side_rook_moved, black_queen_side_rook_moved);

            for (int k = 0; k < piece_moves.size(); k++)
            {
                int new_row = piece_moves[k][0] - '0';
                int new_col = piece_moves[k][2] - '0';

                char piece = chess_board[i][j];
                char temp = chess_board[new_row][new_col];

                chess_board[new_row][new_col] = piece;
                chess_board[i][j] = '.';
                char temp2;

                // Pawn Promotion Move Making Logic
                if (piece_moves[k].size() == 5 && piece_moves[k][4] == 'P')
                {
                    chess_board[new_row][new_col] = piece_moves[k][3];
                }

                // En passant handling
                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'e' && piece_moves[k][4] == 'p')
                {
                    if (current_turn == 'W')
                    {
                        temp2 = chess_board[new_row + 1][new_col];
                        chess_board[new_row + 1][new_col] = '.';
                    }
                    else
                    {
                        temp2 = chess_board[new_row - 1][new_col];
                        chess_board[new_row - 1][new_col] = '.';
                    }
                    ep_moves++;
                }

                // Castling handling
                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'c' && (piece_moves[k][4] == 'k' || piece_moves[k][4] == 'q'))
                {
                    if (current_turn == 'W')
                    {
                        if (piece_moves[k][4] == 'k')
                        {
                            chess_board[7][7] = '.';
                            chess_board[new_row][new_col - 1] = 'R';
                        }
                        else
                        {
                            chess_board[7][0] = '.';
                            chess_board[new_row][new_col + 1] = 'R';
                        }
                    }
                    else
                    {
                        if (piece_moves[k][4] == 'k')
                        {
                            chess_board[0][7] = '.';
                            chess_board[new_row][new_col - 1] = 'r';
                        }
                        else
                        {
                            chess_board[0][0] = '.';
                            chess_board[new_row][new_col + 1] = 'r';
                        }
                    }
                }

                // Castling update
                if (piece == 'K' || piece == 'k')
                {
                    if (current_turn == 'W')
                        white_king_moved = true;
                    else
                        black_king_moved = true;
                }
                if (piece == 'R' || piece == 'r')
                {
                    if (current_turn == 'W')
                    {
                        if (i == 7 && j == 0)
                            white_queen_side_rook_moved = true;
                        if (i == 7 && j == 7)
                            white_king_side_rook_moved = true;
                    }
                    else
                    {
                        if (i == 0 && j == 0)
                            black_queen_side_rook_moved = true;
                        if (i == 0 && j == 7)
                            black_king_side_rook_moved = true;
                    }
                }

                // Count positions for this move
                unsigned long long move_count = 0;
                sample_perft_test(target_depth, chess_board, curr_depth + 1, move_count, i, j, new_row, new_col, ep_moves, (player_turn == 'w') ? 'b' : 'w', castling_moves, promotion_moves);

                // Print the perft count for this move
                if (curr_depth == 1)
                {
                    std::string move_start = std::to_string(i) + "," + std::to_string(j);
                    std::string move_dest = std::to_string(new_row) + "," + std::to_string(new_col);

                    std::string uci_move = convert_indices_to_UCI(move_start, move_dest);

                    std::cout << uci_move << ": " << move_count << std::endl;
                }

                total_positions += move_count;

                // Undo the move
                chess_board[new_row][new_col] = temp;
                chess_board[i][j] = piece;

                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'e' && piece_moves[k][4] == 'p')
                {
                    if (current_turn == 'W')
                        chess_board[new_row + 1][new_col] = temp2;
                    else
                        chess_board[new_row - 1][new_col] = temp2;
                }

                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'c' && (piece_moves[k][4] == 'k' || piece_moves[k][4] == 'q'))
                {
                    if (current_turn == 'W')
                    {
                        if (piece_moves[k][4] == 'k')
                        {
                            chess_board[7][7] = 'R';
                            chess_board[new_row][new_col - 1] = '.';
                        }
                        else
                        {
                            chess_board[7][0] = 'R';
                            chess_board[new_row][new_col + 1] = '.';
                        }
                    }
                    else
                    {
                        if (piece_moves[k][4] == 'k')
                        {
                            chess_board[0][7] = 'r';
                            chess_board[new_row][new_col - 1] = '.';
                        }
                        else
                        {
                            chess_board[0][0] = 'r';
                            chess_board[new_row][new_col + 1] = '.';
                        }
                    }
                }

                white_king_moved = wkm;
                white_king_side_rook_moved = wksrm;
                white_queen_side_rook_moved = wqsrm;
                black_king_moved = bkm;
                black_king_side_rook_moved = bksrm;
                black_queen_side_rook_moved = bqsrm;
            }
        }
    }

    if (curr_depth == 1)
    {
        std::cout << "Total positions: " << total_positions << std::endl;
    }
}

void sample_perft_test(int target_depth, std::vector<std::vector<char>> &chess_board, int curr_depth, unsigned long long int &moves, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, int &ep_moves, char player_turn, long long int &castling_moves, long long int &promotion_moves)
{
    if (curr_depth > target_depth) // Base Case
    {
        return;
    }
    // Backup castling rights before this move
    bool wkm = white_king_moved;
    bool wksrm = white_king_side_rook_moved;
    bool wqsrm = white_queen_side_rook_moved;
    bool bkm = black_king_moved;
    bool bksrm = black_king_side_rook_moved;
    bool bqsrm = black_queen_side_rook_moved;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char curr_square = chess_board[i][j];
            char current_turn = (player_turn == 'w') ? 'W' : 'B';

            if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
            {
                continue;
            }
            std::vector<std::string> piece_moves = generate_legal_moves_for_a_piece(chess_board, current_turn, i, j, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j, white_king_moved, white_king_side_rook_moved, white_queen_side_rook_moved, black_king_moved, black_king_side_rook_moved, black_queen_side_rook_moved);

            for (int k = 0; k < piece_moves.size(); k++)
            {
                int new_row = piece_moves[k][0] - '0'; // Convert char to int
                int new_col = piece_moves[k][2] - '0'; // Convert char to int

                char piece = chess_board[i][j];
                char temp = chess_board[new_row][new_col];

                chess_board[new_row][new_col] = piece;
                chess_board[i][j] = '.';
                char temp2;
                char temp_castle;

                // Pawn Promotion Move Making Logic
                if (piece_moves[k].size() == 5 && piece_moves[k][4] == 'P')
                {
                    chess_board[new_row][new_col] = piece_moves[k][3];

                    if (curr_depth == target_depth) // Counting the total number of promotions occuring
                        promotion_moves++;
                }

                // enapassant move making logic
                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'e' && piece_moves[k][4] == 'p')
                {
                    if (current_turn == 'W')
                    {
                        temp2 = chess_board[new_row + 1][new_col];
                        chess_board[new_row + 1][new_col] = '.';
                    }
                    else
                    {
                        temp2 = chess_board[new_row - 1][new_col];
                        chess_board[new_row - 1][new_col] = '.';
                    }
                    if (curr_depth == target_depth) // Only Counting Enpassant Moves for the current depth
                        ep_moves++;
                }
                // Castling Move Making Logic
                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'c' && (piece_moves[k][4] == 'k' || piece_moves[k][4] == 'q'))
                {
                    if (current_turn == 'W')
                    {
                        if (piece_moves[k][4] == 'k') // Kingside Castle
                        {
                            chess_board[7][7] = '.';
                            chess_board[new_row][new_col - 1] = 'R';
                        }
                        else // Queenside Castle
                        {
                            chess_board[7][0] = '.';
                            chess_board[new_row][new_col + 1] = 'R';
                        }
                    }
                    else
                    {
                        if (piece_moves[k][4] == 'k') // Kingside Castle
                        {
                            chess_board[0][7] = '.';
                            chess_board[new_row][new_col - 1] = 'r';
                        }
                        else // Queenside Castle
                        {
                            chess_board[0][0] = '.';
                            chess_board[new_row][new_col + 1] = 'r';
                        }
                    }

                    if (curr_depth == target_depth) // Used For Tracking Castling Moves
                        castling_moves++;
                }

                // Handle Castling Updates
                if (piece == 'K' || piece == 'k') // Check for both kings
                {
                    if (piece == 'K') // White King
                        white_king_moved = true;
                    else if (piece == 'k') // Black King
                        black_king_moved = true;
                }
                // Shady Line
                if (piece == 'R' || piece == 'r') // Check for both rooks
                {
                    if (piece == 'R') // White Rook
                    {
                        if (i == 7 && j == 0)
                            white_queen_side_rook_moved = true;
                        if (i == 7 && j == 7)
                            white_king_side_rook_moved = true;
                    }
                    else if (piece == 'r') // Black Rook
                    {
                        if (i == 0 && j == 0)
                            black_queen_side_rook_moved = true;
                        if (i == 0 && j == 7)
                            black_king_side_rook_moved = true;
                    }
                }

                if (curr_depth == target_depth) // Used For Tracking Overall Moves
                    moves++;

                sample_perft_test(target_depth, chess_board, curr_depth + 1, moves, i, j, new_row, new_col, ep_moves, (player_turn == 'w') ? 'b' : 'w', castling_moves, promotion_moves);

                chess_board[new_row][new_col] = temp;
                chess_board[i][j] = piece;

                // Enpassant Move Unmaking Logic
                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'e' && piece_moves[k][4] == 'p')
                {
                    if (current_turn == 'W')
                        chess_board[new_row + 1][new_col] = temp2;
                    else
                        chess_board[new_row - 1][new_col] = temp2;
                }

                // Castling Move Unmaking Logic
                if (piece_moves[k].size() == 5 && piece_moves[k][3] == 'c' && (piece_moves[k][4] == 'k' || piece_moves[k][4] == 'q'))
                {
                    if (current_turn == 'W')
                    {
                        if (piece_moves[k][4] == 'k') // Kingside Castle
                        {
                            chess_board[7][7] = 'R';
                            chess_board[new_row][new_col - 1] = '.';
                        }
                        else // Queenside Castle
                        {
                            chess_board[7][0] = 'R';
                            chess_board[new_row][new_col + 1] = '.';
                        }
                    }
                    else
                    {
                        if (piece_moves[k][4] == 'k') // Kingside Castle
                        {
                            chess_board[0][7] = 'r';
                            chess_board[new_row][new_col - 1] = '.';
                        }
                        else // Queenside Castle
                        {
                            chess_board[0][0] = 'r';
                            chess_board[new_row][new_col + 1] = '.';
                        }
                    }
                }

                white_king_moved = wkm;
                white_king_side_rook_moved = wksrm;
                white_queen_side_rook_moved = wqsrm;
                black_king_moved = bkm;
                black_king_side_rook_moved = bksrm;
                black_queen_side_rook_moved = bqsrm;
            }
        }
    }
}

std::vector<std::string> generate_legal_moves_for_a_piece(std::vector<std::vector<char>> &chess_board, char player_color, int row, int col, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, bool &white_king_moved, bool &white_king_side_rook_moved, bool &white_queen_side_rook_moved, bool &black_king_moved, bool &black_king_side_rook_moved, bool &black_queen_side_rook_moved)
{
    char piece = chess_board[row][col];
    std::vector<std::string> moves_generated;

    // Pawns
    if (piece == 'P' || piece == 'p')
    {
        // Choosing to move one square forward
        if ((piece == 'P' && row > 0 && chess_board[row - 1][col] == '.') || (piece == 'p' && row < 7 && chess_board[row + 1][col] == '.'))
        {
            if (piece == 'P') // White Pawn
            {
                if (row == 1) // If moving to rank 8, handle promotion
                {
                    if (is_legal_after_move(chess_board, row, col, row - 1, col, player_color))
                    {
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col) + "QP"); // 'P' for promotion
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col) + "RP");
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col) + "BP");
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col) + "NP");
                    }
                }
                else // Normal pawn move
                {
                    if (is_legal_after_move(chess_board, row, col, row - 1, col, player_color))
                    {
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col));
                    }
                }
            }

            if (piece == 'p') // Black Pawn
            {
                if (row == 6) // If moving to rank 1, handle promotion
                {
                    if (is_legal_after_move(chess_board, row, col, row + 1, col, player_color))
                    {
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col) + "qP"); // 'P' for promotion
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col) + "rP");
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col) + "bP");
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col) + "nP");
                    }
                }
                else // Normal pawn move
                {
                    if (is_legal_after_move(chess_board, row, col, row + 1, col, player_color))
                    {
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col));
                    }
                }
            }
        }

        // Checking For Captures
        if (piece == 'P' && row > 0) // White Pawn
        {
            if (col > 0 && islower(chess_board[row - 1][col - 1])) // Capture left
            {
                if (row == 1) // Promotion
                {
                    if (is_legal_after_move(chess_board, row, col, row - 1, col - 1, player_color))
                    {
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col - 1) + "QP"); // 'P' for promotion
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col - 1) + "RP");
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col - 1) + "BP");
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col - 1) + "NP");
                    }
                }
                else if (is_legal_after_move(chess_board, row, col, row - 1, col - 1, player_color))
                {
                    moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col - 1));
                }
            }

            if (col < 7 && islower(chess_board[row - 1][col + 1])) // Capture right
            {
                if (row == 1) // Promotion
                {
                    if (is_legal_after_move(chess_board, row, col, row - 1, col + 1, player_color))
                    {
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col + 1) + "QP"); // 'P' for promotion
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col + 1) + "RP");
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col + 1) + "BP");
                        moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col + 1) + "NP");
                    }
                }
                else if (is_legal_after_move(chess_board, row, col, row - 1, col + 1, player_color))
                {
                    moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col + 1));
                }
            }
        }

        if (piece == 'p' && row < 7) // Black Pawn
        {
            if (col > 0 && isupper(chess_board[row + 1][col - 1])) // Capture left
            {
                if (row == 6) // Promotion
                {
                    if (is_legal_after_move(chess_board, row, col, row + 1, col - 1, player_color))
                    {
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col - 1) + "qP"); // 'P' for promotion
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col - 1) + "rP");
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col - 1) + "bP");
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col - 1) + "nP");
                    }
                }
                else if (is_legal_after_move(chess_board, row, col, row + 1, col - 1, player_color))
                {
                    moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col - 1));
                }
            }

            if (col < 7 && isupper(chess_board[row + 1][col + 1])) // Capture right
            {
                if (row == 6) // Promotion
                {
                    if (is_legal_after_move(chess_board, row, col, row + 1, col + 1, player_color))
                    {
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col + 1) + "qP"); // 'P' for promotion
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col + 1) + "rP");
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col + 1) + "bP");
                        moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col + 1) + "nP");
                    }
                }
                else if (is_legal_after_move(chess_board, row, col, row + 1, col + 1, player_color))
                {
                    moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col + 1));
                }
            }
        }

        // Checking For Two Moves from the Start
        if ((piece == 'P' && row == 6 && chess_board[row - 1][col] == '.' && chess_board[row - 2][col] == '.') ||
            (piece == 'p' && row == 1 && chess_board[row + 1][col] == '.' && chess_board[row + 2][col] == '.'))
        {
            if (piece == 'P' && is_legal_after_move(chess_board, row, col, row - 2, col, player_color))
            {
                moves_generated.push_back(std::to_string(row - 2) + "," + std::to_string(col));
            }

            if (piece == 'p' && is_legal_after_move(chess_board, row, col, row + 2, col, player_color))
            {
                moves_generated.push_back(std::to_string(row + 2) + "," + std::to_string(col));
            }
        }

        // en-passant logic
        if (opp_move_dest_i != -1) // If it's NOT the first move of the game
        {
            if (piece == 'P' && row == 3 && chess_board[opp_move_dest_i][opp_move_dest_j] == 'p' && opp_move_start_i == 1 &&
                opp_move_dest_i == 3 && (col == opp_move_dest_j - 1 || col == opp_move_dest_j + 1))
            {
                // Simulate the en passant move
                char temp = chess_board[opp_move_dest_i - 1][opp_move_dest_j]; // Store what was there
                chess_board[opp_move_dest_i][opp_move_dest_j] = '.';           // Remove the captured pawn
                chess_board[row][col] = '.';                                   // Move the pawn
                chess_board[opp_move_dest_i - 1][opp_move_dest_j] = 'P';

                // Check if this exposes the king
                bool is_still_legal = !king_in_check(chess_board, player_color);

                // Undo the move
                chess_board[opp_move_dest_i][opp_move_dest_j] = 'p';
                chess_board[row][col] = 'P';
                chess_board[opp_move_dest_i - 1][opp_move_dest_j] = temp;

                // If the king is not in check, add the move
                if (is_still_legal)
                {
                    moves_generated.push_back(std::to_string(opp_move_dest_i - 1) + "," + std::to_string(opp_move_dest_j) + "ep");
                }
            }

            if (piece == 'p' && row == 4 && chess_board[opp_move_dest_i][opp_move_dest_j] == 'P' && opp_move_start_i == 6 &&
                opp_move_dest_i == 4 && (col == opp_move_dest_j - 1 || col == opp_move_dest_j + 1))
            {
                // Simulate the en passant move
                char temp = chess_board[opp_move_dest_i + 1][opp_move_dest_j]; // Store what was there
                chess_board[opp_move_dest_i][opp_move_dest_j] = '.';           // Remove the captured pawn
                chess_board[row][col] = '.';                                   // Move the pawn
                chess_board[opp_move_dest_i + 1][opp_move_dest_j] = 'p';

                // Check if this exposes the king
                bool is_still_legal = !king_in_check(chess_board, player_color);

                // Undo the move
                chess_board[opp_move_dest_i][opp_move_dest_j] = 'P';
                chess_board[row][col] = 'p';
                chess_board[opp_move_dest_i + 1][opp_move_dest_j] = temp;

                // If the king is not in check, add the move
                if (is_still_legal)
                {
                    moves_generated.push_back(std::to_string(opp_move_dest_i + 1) + "," + std::to_string(opp_move_dest_j) + "ep");
                }
            }
        }
    }

    // Rooks
    if (piece == 'R' || piece == 'r')
    {
        // Possible move directions for Rook
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

        for (auto &dir : directions)
        {
            int k = row + dir[0], l = col + dir[1];

            while (k >= 0 && k < 8 && l >= 0 && l < 8)
            {
                if (chess_board[k][l] != '.')
                {
                    // If friendly piece, stop
                    if ((player_color == 'W' && isupper(chess_board[k][l])) || (player_color == 'B' && islower(chess_board[k][l])))
                    {
                        break;
                    }

                    // If opposition piece, check legality, capture & stop
                    if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                    {
                        moves_generated.push_back(std::to_string(k) + "," + std::to_string(l));
                    }
                    break;
                }

                if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                {
                    moves_generated.push_back(std::to_string(k) + "," + std::to_string(l));
                }

                k += dir[0];
                l += dir[1];
            }
        }
    }

    // Bishop Optimized
    if (piece == 'B' || piece == 'b')
    {
        int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (auto &dir : directions)
        {
            int dx = dir[0], dy = dir[1];
            int k = row + dx, l = col + dy;

            while (k >= 0 && k < 8 && l >= 0 && l < 8)
            {
                char piece_at_pos = chess_board[k][l];

                if (piece_at_pos != '.')
                {
                    if ((player_color == 'W' && isupper(piece_at_pos)) || (player_color == 'B' && islower(piece_at_pos)))
                        break; // Friendly piece blocks path.

                    if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                        moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Capture move.

                    break;
                }

                if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                    moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Empty square move.

                k += dx;
                l += dy;
            }
        }
    }
    // Queen Optimized
    if (piece == 'Q' || piece == 'q')
    {
        int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, // Rook moves (Up, Down, Left, Right)
                                {-1, -1},
                                {-1, 1},
                                {1, -1},
                                {1, 1}}; // Bishop moves (Diagonal)

        for (auto &dir : directions)
        {
            int dx = dir[0], dy = dir[1];
            int k = row + dx, l = col + dy;

            while (k >= 0 && k < 8 && l >= 0 && l < 8)
            {
                char piece_at_pos = chess_board[k][l];

                if (piece_at_pos != '.')
                {
                    if ((player_color == 'W' && isupper(piece_at_pos)) || (player_color == 'B' && islower(piece_at_pos)))
                        break; // Friendly piece blocks path.

                    if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                        moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Capture move.

                    break;
                }

                if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                    moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Empty square move.

                k += dx;
                l += dy;
            }
        }
    }

    // Knight Optimzied
    if (piece == 'N' || piece == 'n')
    {
        int knight_moves[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

        for (auto &move : knight_moves)
        {
            int k = row + move[0], l = col + move[1];

            if (k >= 0 && k < 8 && l >= 0 && l < 8) // Ensure move is within board limits
            {
                char piece_at_pos = chess_board[k][l];

                if (piece_at_pos == '.' || (player_color == 'W' && islower(piece_at_pos)) || (player_color == 'B' && isupper(piece_at_pos)))
                {
                    if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                        moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Add valid move.
                }
            }
        }
    }

    // King Move Generation
    if (piece == 'K' || piece == 'k')
    {
        int king_moves[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1}, // Top row
            {0, -1},
            {0, 1}, // Left and Right
            {1, -1},
            {1, 0},
            {1, 1} // Bottom row
        };

        for (auto &move : king_moves)
        {
            int k = row + move[0], l = col + move[1];

            if (k >= 0 && k < 8 && l >= 0 && l < 8) // Ensure move is within board limits
            {
                char piece_at_pos = chess_board[k][l];

                if (piece_at_pos == '.' || (player_color == 'W' && islower(piece_at_pos)) || (player_color == 'B' && isupper(piece_at_pos)))
                {
                    if (is_legal_after_move(chess_board, row, col, k, l, player_color))
                    {
                        moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Add valid move.
                    }
                }
            }
        }

        if ((player_color == 'W' && !white_king_moved) || (player_color == 'B' && !black_king_moved))
        {
            int back_rank = (player_color == 'W') ? 7 : 0; // White's back rank is 7, Black's is 0

            // King-side castling (O-O)
            if (((player_color == 'W' && !white_king_side_rook_moved) || (player_color == 'B' && !black_king_side_rook_moved)) &&
                chess_board[back_rank][5] == '.' && chess_board[back_rank][6] == '.' && ((player_color == 'W' && chess_board[back_rank][7] == 'R') || (player_color == 'B' && chess_board[back_rank][7] == 'r')) &&
                !(king_in_check(chess_board, player_color)) &&
                is_legal_after_move(chess_board, row, col, back_rank, 5, player_color) &&
                is_legal_after_move(chess_board, row, col, back_rank, 6, player_color))
            {
                moves_generated.push_back(std::to_string(back_rank) + ",6" + "ck"); // King moves to g-file
            }

            // Queen-side castling (O-O-O)
            if (((player_color == 'W' && !white_queen_side_rook_moved) || (player_color == 'B' && !black_queen_side_rook_moved)) &&
                chess_board[back_rank][1] == '.' && chess_board[back_rank][2] == '.' && chess_board[back_rank][3] == '.' && ((player_color == 'W' && chess_board[back_rank][0] == 'R') || (player_color == 'B' && chess_board[back_rank][0] == 'r')) &&
                !(king_in_check(chess_board, player_color)) &&
                is_legal_after_move(chess_board, row, col, back_rank, 2, player_color) &&
                is_legal_after_move(chess_board, row, col, back_rank, 3, player_color))
            {
                moves_generated.push_back(std::to_string(back_rank) + ",2" + "cq"); // King moves to c-file
            }
        }
    }
    return moves_generated; // Returns all valid moves for that piece as a vector<string>
}

bool is_legal_move_available(std::vector<std::vector<char>> &chess_board, char current_turn,int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j)
{
    bool t = true;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char curr_square = chess_board[i][j];

            if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
            {
                continue;
            }

            std::vector<std::string> moves = generate_legal_moves_for_a_piece(chess_board, 'W', i, j,opp_move_start_i,opp_move_start_j,opp_move_dest_i,opp_move_dest_j,t,t,t,t,t,t); // Extracting Valid moves Per piece
            if(!moves.empty())
            {
                return true;
            }
        }
    }
    return false;
}

bool is_checkmate(std::vector<std::vector<char>> &chess_board, char current_turn,int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j)
{
    // Check if the king is in check.
    bool is_king_in_check = king_in_check(chess_board,current_turn);
    
    // Check if there are any legal moves available.
    bool legal_moves_available = is_legal_move_available(chess_board, current_turn, opp_move_start_i,opp_move_start_j,opp_move_dest_i,opp_move_dest_j);
    
    // If the king is in check and no legal moves are available, it's checkmate.
    if (is_king_in_check && !legal_moves_available)
    {
        return true; // Checkmate
    }

    return false; // Not checkmate
}

bool is_stalemate(std::vector<std::vector<char>> &chess_board, char current_turn, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j)
{
    // Check if the king is in check.
    bool is_king_in_check = king_in_check(chess_board, current_turn);
    
    // Check if there are any legal moves available.
    bool legal_moves_available = is_legal_move_available(chess_board, current_turn, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j);
    
    // If the king is not in check and no legal moves are available, it's stalemate.
    if (!is_king_in_check && !legal_moves_available)
    {
        return true; // Stalemate
    }

    return false; // Not stalemate
}


// Under Development

int print_all_legal_moves_for_a_position(std::vector<std::vector<char>> &chess_board, char player_color, std::unordered_map<char, std::string> &chess_pieces)
{
    long long int total_moves = 0; // Stores the number of possible Move variations of every piece combined
    int ep_moves = 0;

    std::cout << "Printing all Legal Moves in the position piece by piece\n";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess_board[i][j] != '.' && player_color == 'W' && isupper(chess_board[i][j]))
            {
                std::vector<std::string> moves = generate_legal_moves_for_a_piece(chess_board, 'W', i, j, -1, -1, -1, -1, white_king_moved, white_king_side_rook_moved, white_queen_side_rook_moved, black_king_moved, black_king_side_rook_moved, black_queen_side_rook_moved); // Extracting Valid moves Per piece
                std::cout << chess_pieces[chess_board[i][j]] << " At Position " << (char)('A' + j) << 8 - i << " is -> ";

                total_moves += moves.size(); // Counting all Moves

                for (int k = 0; k < moves.size(); k++) // Printing Moves
                {
                    std::cout << convert_indices_to_UCI(std::to_string(i) + "," + std::to_string(j), moves[k]) << " ";
                }
                if (moves.size() == 0)
                {
                    std::cout << " No Possible Moves";
                }
                std::cout << std::endl;
            }

            if (chess_board[i][j] != '.' && player_color == 'B' && islower(chess_board[i][j]))
            {
                std::vector<std::string> moves = generate_legal_moves_for_a_piece(chess_board, 'B', i, j, -1, -1, -1, -1, white_king_moved, white_king_side_rook_moved, white_queen_side_rook_moved, black_king_moved, black_king_side_rook_moved, black_queen_side_rook_moved); // Extracting Valid moves Per piece
                std::cout << chess_pieces[chess_board[i][j]] << " At Position " << (char)('A' + j) << 8 - i << " is -> ";

                total_moves += moves.size(); // Counting all moves

                for (int k = 0; k < moves.size(); k++) // Printing Moves
                {
                    std::cout << convert_indices_to_UCI(std::to_string(i) + "," + std::to_string(j), moves[k]) << " ";
                }

                if (moves.size() == 0)
                {
                    std::cout << " No Possible Moves";
                }
                std::cout << std::endl;
            }
        }
    }
    return total_moves;
}
