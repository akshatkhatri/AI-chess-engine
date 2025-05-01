#include "Search.h"
#include "Evaluation.h"
#include "legalmoves.h"
#include <vector>
#include <string>
#include <iostream>
#include<climits>



std::string minimax_driver(int target_depth, std::vector<std::vector<char>> &chess_board, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, char current_turn, bool &_white_king_moved, bool &_white_king_side_rook_moved, bool &_white_queen_side_rook_moved, bool &_black_king_moved, bool &_black_king_side_rook_moved, bool &_black_queen_side_rook_moved)
{
    int best_move_start_i = -1;
    int best_move_start_j = -1;
    int best_move_dest_i = -1;
    int best_move_dest_j = -1;

    int BEST_SCORE = INT_MIN; // equivalent to minus infinity

    // Backup castling rights before this move
    bool wkm = _white_king_moved;
    bool wksrm = _white_king_side_rook_moved;
    bool wqsrm = _white_queen_side_rook_moved;
    bool bkm = _black_king_moved;
    bool bksrm = _black_king_side_rook_moved;
    bool bqsrm = _black_queen_side_rook_moved;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char curr_square = chess_board[i][j];
            // char current_turn = 'W';

            if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
            {
                continue;
            }
            std::vector<std::string> piece_moves = generate_legal_moves_for_a_piece(chess_board, current_turn, i, j, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j, _white_king_moved, _white_king_side_rook_moved, _white_queen_side_rook_moved, _black_king_moved, _black_king_side_rook_moved,_black_queen_side_rook_moved);

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
                }

                // Handle Castling Updates
                if (piece == 'K' || piece == 'k') // Check for both kings
                {
                    if (piece == 'K') // White King
                        _white_king_moved = true;
                    else if (piece == 'k') // Black King
                        _black_king_moved = true;
                }
                // Shady Line
                if (piece == 'R' || piece == 'r') // Check for both rooks
                {
                    if (piece == 'R') // White Rook
                    {
                        if (i == 7 && j == 0)
                            _white_queen_side_rook_moved = true;
                        if (i == 7 && j == 7)
                            _white_king_side_rook_moved = true;
                    }
                    else if (piece == 'r') // Black Rook
                    {

                        if (i == 0 && j == 0)
                           _black_queen_side_rook_moved = true;
                        if (i == 0 && j == 7)
                            _black_king_side_rook_moved = true;
                    }
                }

                // sample_perft_test(target_depth, chess_board, curr_depth + 1, moves, i, j, new_row, new_col, ep_moves, (player_turn == 'w') ? 'b' : 'w', castling_moves,promotion_moves);
                // bool maximizingPlayer = (current_turn == 'W') ? true : false; // AI's turn is maximizing or minimizing
                int score = minimax(chess_board, target_depth, INT_MIN, INT_MAX, false, (current_turn == 'W') ? 'B' : 'W', current_turn, i, j, new_row, new_col,_white_king_moved,_white_king_side_rook_moved,_white_queen_side_rook_moved,_black_king_moved,_black_king_moved,_black_queen_side_rook_moved);

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

                _white_king_moved = wkm;
                _white_king_side_rook_moved = wksrm;
                _white_queen_side_rook_moved = wqsrm;
                _black_king_moved = bkm;
                _black_king_side_rook_moved = bksrm;
                _black_queen_side_rook_moved = bqsrm;

                // std::cout<<score<<std::endl;

                if (score > BEST_SCORE) // Candidate Best Score And Move
                {
                    BEST_SCORE = score;
                    best_move_start_i = i;
                    best_move_start_j = j;
                    best_move_dest_i = new_row;
                    best_move_dest_j = new_col;
                }
            }
        }
    }
    // std::cout << "Best Evaluation Possible -> " << BEST_SCORE << std::endl;
    return std::to_string(best_move_start_i) + "," + std::to_string(best_move_start_j) + "|" + std::to_string(best_move_dest_i) + "," + std::to_string(best_move_dest_j);
}

int minimax(std::vector<std::vector<char>> &chess_board, int depth, int alpha, int beta, bool maximizing_player, char current_turn, char ai_color, int opp_move_start_i, int opp_move_start_j, int opp_move_dest_i, int opp_move_dest_j, bool &_white_king_moved, bool &_white_king_side_rook_moved, bool &_white_queen_side_rook_moved, bool &_black_king_moved, bool &_black_king_side_rook_moved, bool &_black_queen_side_rook_moved)
{
    // std::cout<<"Here"<<std::endl;
    if (depth == 0 || is_checkmate(chess_board, current_turn, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j) || is_stalemate(chess_board, current_turn, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j)) // Base Case
    {
        return static_evaluate(chess_board, ai_color,current_turn);
    }

    // Backup castling rights before this move
    bool wkm = _white_king_moved;
    bool wksrm = _white_king_side_rook_moved;
    bool wqsrm = _white_queen_side_rook_moved;
    bool bkm = _black_king_moved;
    bool bksrm = _black_king_side_rook_moved;
    bool bqsrm = _black_queen_side_rook_moved;

    if (maximizing_player)
    {
        int max_eval = INT_MIN;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                char curr_square = chess_board[i][j];

                if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
                {
                    continue;
                }
                std::vector<std::string> piece_moves = generate_legal_moves_for_a_piece(chess_board, current_turn, i, j, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j, _white_king_moved, _white_king_side_rook_moved, _white_queen_side_rook_moved, _black_king_moved, _black_king_side_rook_moved,_black_queen_side_rook_moved);

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
                    }

                    // Handle Castling Updates
                    if (piece == 'K' || piece == 'k') // Check for both kings
                    {
                        if (piece == 'K') // White King
                            _white_king_moved = true;
                        else if (piece == 'k') // Black King
                            _black_king_moved = true;
                    }
                    // Shady Line
                    if (piece == 'R' || piece == 'r') // Check for both rooks
                    {
                        if (piece == 'R') // White Rook
                        {
                            if (i == 7 && j == 0)
                                _white_queen_side_rook_moved = true;
                            if (i == 7 && j == 7)
                                _white_king_side_rook_moved = true;
                        }
                        else if (piece == 'r') // Black Rook
                        {
                            if (i == 0 && j == 0)
                               _black_queen_side_rook_moved = true;
                            if (i == 0 && j == 7)
                                _black_king_side_rook_moved = true;
                        }
                    }

                    // sample_perft_test(target_depth, chess_board, curr_depth + 1, moves, i, j, new_row, new_col, ep_moves, (player_turn == 'w') ? 'b' : 'w', castling_moves, promotion_moves);
                    int eval = minimax(chess_board, depth - 1, alpha, beta, false, (current_turn == 'W') ? 'B' : 'W', ai_color, i, j, new_row, new_col,_white_king_moved,_white_king_side_rook_moved,_white_queen_side_rook_moved,_black_king_moved,_black_king_side_rook_moved,_black_queen_side_rook_moved);
                    // std::cout<<eval<<std::endl;
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

                    _white_king_moved = wkm;
                    _white_king_side_rook_moved = wksrm;
                    _white_queen_side_rook_moved = wqsrm;
                    _black_king_moved = bkm;
                    _black_king_side_rook_moved = bksrm;
                    _black_queen_side_rook_moved = bqsrm;

                    max_eval = std::max(max_eval, eval);
                    alpha = std::max(alpha, eval);

                    if (beta <= alpha)
                        break; // Beta cut-off
                }
            }
        }
        return max_eval;
    }
    else
    {
        int min_eval = INT_MAX;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                char curr_square = chess_board[i][j];

                if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
                {
                    continue;
                }
                std::vector<std::string> piece_moves = generate_legal_moves_for_a_piece(chess_board, current_turn, i, j, opp_move_start_i, opp_move_start_j, opp_move_dest_i, opp_move_dest_j, _white_king_moved, _white_king_side_rook_moved, _white_queen_side_rook_moved, _black_king_moved, _black_king_side_rook_moved,_black_queen_side_rook_moved);

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
                    }

                    // Handle Castling Updates
                    if (piece == 'K' || piece == 'k') // Check for both kings
                    {
                        if (piece == 'K') // White King
                            _white_king_moved = true;
                        else if (piece == 'k') // Black King
                            _black_king_moved = true;
                    }
                    // Shady Line
                    if (piece == 'R' || piece == 'r') // Check for both rooks
                    {
                        if (piece == 'R') // White Rook
                        {
                            if (i == 7 && j == 0)
                                _white_queen_side_rook_moved = true;
                            if (i == 7 && j == 7)
                                _white_king_side_rook_moved = true;
                        }
                        else if (piece == 'r') // Black Rook
                        {
                            if (i == 0 && j == 0)
                               _black_queen_side_rook_moved = true;
                            if (i == 0 && j == 7)
                                _black_king_side_rook_moved = true;
                        }
                    }

                    // sample_perft_test(target_depth, chess_board, curr_depth + 1, moves, i, j, new_row, new_col, ep_moves, (player_turn == 'w') ? 'b' : 'w', castling_moves, promotion_moves);
                    int eval = minimax(chess_board, depth - 1, alpha, beta, true, (current_turn == 'W') ? 'B' : 'W', ai_color, i, j, new_row, new_col,_white_king_moved,_white_king_side_rook_moved,_white_queen_side_rook_moved,_black_king_moved,_black_king_side_rook_moved,_black_queen_side_rook_moved);
                    // std::cout<<eval<<std::endl;

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

                    _white_king_moved = wkm;
                    _white_king_side_rook_moved = wksrm;
                    _white_queen_side_rook_moved = wqsrm;
                    _black_king_moved = bkm;
                    _black_king_side_rook_moved = bksrm;
                    _black_queen_side_rook_moved = bqsrm;

                    min_eval = std::min(min_eval, eval);
                    beta = std::min(beta, eval);

                    if (beta <= alpha)
                        break; // Beta cut-off
                }
            }
        }
        return min_eval;
    }
}
