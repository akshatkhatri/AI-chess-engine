#include "legalmoves.h"
#include "king_check.h"
#include "notations.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
// TO-DO

// unsigned long long int moves = 0; // Move Tracker
long long int depth2_moves = 0;

void sample_perft_test(int target_depth, std::vector<std::vector<char>> &chess_board, int curr_depth, unsigned long long int &moves)
{
    if (curr_depth > target_depth) // Base Case
    {
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char current_turn = curr_depth % 2 == 1 ? 'W' : 'B';
            char curr_square = chess_board[i][j];

            if (curr_square == '.' || (current_turn == 'W' && islower(curr_square)) || (current_turn == 'B' && isupper(curr_square)))
            {
                continue;
            }
            std::vector<std::string> piece_moves = generate_legal_moves_for_a_piece(chess_board, current_turn, i, j);

                for (int k = 0; k < piece_moves.size(); k++)
                {
                    int new_row = piece_moves[k][0] - '0'; // Convert char to int
                    int new_col = piece_moves[k][2] - '0'; // Convert char to int

                    char piece = chess_board[i][j];
                    char temp = chess_board[new_row][new_col];

                    chess_board[new_row][new_col] = piece;
                    chess_board[i][j] = '.';

                    if(curr_depth == target_depth)
                        moves++;

                    sample_perft_test(target_depth, chess_board, curr_depth + 1, moves);

                    chess_board[new_row][new_col] = temp;
                    chess_board[i][j] = piece;
                }
        }
    }
}

std::vector<std::string> generate_legal_moves_for_a_piece(std::vector<std::vector<char>> &chess_board, char player_color, int row, int col)
{
    char piece = chess_board[row][col];
    std::vector<std::string> moves_generated;

    // Pawns
    if (piece == 'P' || piece == 'p')
    {
        // Choosing to move one square forward
        if ((piece == 'P' && chess_board[row - 1][col] == '.') || (piece == 'p' && chess_board[row + 1][col] == '.'))
        {
            if (piece == 'P' && is_legal_after_move(chess_board, row, col, row - 1, col, player_color))
            {
                moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col));
            }

            if (piece == 'p' && is_legal_after_move(chess_board, row, col, row + 1, col, player_color))
            {
                moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col));
            }
        }
        // Checking For Captures
        if ((piece == 'P' && row > 0 && col > 0 && islower(chess_board[row - 1][col - 1]) && is_legal_after_move(chess_board, row, col, row - 1, col - 1, player_color)) ||
            (piece == 'P' && row > 0 && col < 7 && islower(chess_board[row - 1][col + 1]) && is_legal_after_move(chess_board, row, col, row - 1, col + 1, player_color)) ||
            (piece == 'p' && row < 7 && col > 0 && isupper(chess_board[row + 1][col - 1]) && is_legal_after_move(chess_board, row, col, row + 1, col - 1, player_color)) ||
            (piece == 'p' && row < 7 && col < 7 && isupper(chess_board[row + 1][col + 1]) && is_legal_after_move(chess_board, row, col, row + 1, col + 1, player_color)))
        {
            if (piece == 'P' && row > 0)
            { // White pawn
                if (col > 0 && islower(chess_board[row - 1][col - 1]))
                    moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col - 1));

                if (col < 7 && islower(chess_board[row - 1][col + 1]))
                    moves_generated.push_back(std::to_string(row - 1) + "," + std::to_string(col + 1));
            }
            if (piece == 'p' && row < 7)
            { // Black pawn
                if (col > 0 && isupper(chess_board[row + 1][col - 1]))
                    moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col - 1));

                if (col < 7 && isupper(chess_board[row + 1][col + 1]))
                    moves_generated.push_back(std::to_string(row + 1) + "," + std::to_string(col + 1));
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

        /*

        Pending En-Passant and Promotion Logic

        */
    }

    // Rooks
    if (piece == 'R' || piece == 'r')
    {
        // Upward movement for Rook
        for (int k = row - 1; k >= 0; k--)
        {
            if (chess_board[k][col] != '.' && ((player_color == 'W' && isupper(chess_board[k][col])) || (player_color == 'B' && islower(chess_board[k][col]))))
            {
                // Friendly piece encountered, stop
                break;
            }

            if (chess_board[k][col] != '.' && ((player_color == 'W' && islower(chess_board[k][col])) || (player_color == 'B' && isupper(chess_board[k][col]))))
            {
                // Opposition piece encountered, capture & stop
                if (is_legal_after_move(chess_board, row, col, k, col, player_color))
                    moves_generated.push_back(std::to_string(k) + "," + std::to_string(col)); // Add move

                break;
            }
            if (is_legal_after_move(chess_board, row, col, k, col, player_color))
                moves_generated.push_back(std::to_string(k) + "," + std::to_string(col)); // Add move
        }

        // Down
        for (int k = row + 1; k < 8; k++)
        {
            if (chess_board[k][col] != '.' && ((player_color == 'W' && isupper(chess_board[k][col])) || (player_color == 'B' && islower(chess_board[k][col]))))
            {
                // Friendly piece encountered, stop
                break;
            }

            if (chess_board[k][col] != '.' && ((player_color == 'W' && islower(chess_board[k][col])) || (player_color == 'B' && isupper(chess_board[k][col]))))
            {
                // Opposition piece encountered, capture & stop
                if (is_legal_after_move(chess_board, row, col, k, col, player_color))
                    moves_generated.push_back(std::to_string(k) + "," + std::to_string(col)); // Add move

                break;
            }
            if (is_legal_after_move(chess_board, row, col, k, col, player_color))
                moves_generated.push_back(std::to_string(k) + "," + std::to_string(col)); // Add move
        }
        // Left
        for (int k = col - 1; k >= 0; k--)
        {
            if (chess_board[row][k] != '.' && ((player_color == 'W' && isupper(chess_board[row][k])) || (player_color == 'B' && islower(chess_board[row][k]))))
            {
                // Friendly piece encountered, stop
                break;
            }

            if (chess_board[row][k] != '.' && ((player_color == 'W' && islower(chess_board[row][k])) || (player_color == 'B' && isupper(chess_board[row][k]))))
            {
                // Opposition piece encountered, capture & stop
                if (is_legal_after_move(chess_board, row, col, row, k, player_color))
                    moves_generated.push_back(std::to_string(row) + "," + std::to_string(k)); // Add move

                break;
            }
            if (is_legal_after_move(chess_board, row, col, row, k, player_color))
                moves_generated.push_back(std::to_string(row) + "," + std::to_string(k)); // Add move
        }
        // Right
        for (int k = col + 1; k < 8; k++)
        {
            if (chess_board[row][k] != '.' && ((player_color == 'W' && isupper(chess_board[row][k])) || (player_color == 'B' && islower(chess_board[row][k]))))
            {
                // Friendly piece encountered, stop
                break;
            }

            if (chess_board[row][k] != '.' && ((player_color == 'W' && islower(chess_board[row][k])) || (player_color == 'B' && isupper(chess_board[row][k]))))
            {
                // Opposition piece encountered, capture & stop
                if (is_legal_after_move(chess_board, row, col, row, k, player_color))
                    moves_generated.push_back(std::to_string(row) + "," + std::to_string(k)); // Add move

                break;
            }
            if (is_legal_after_move(chess_board, row, col, row, k, player_color))
                moves_generated.push_back(std::to_string(row) + "," + std::to_string(k)); // Add move
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
                        moves_generated.push_back(std::to_string(k) + "," + std::to_string(l)); // Add valid move.
                }
            }
        }
    }

    return moves_generated; // Returns all valid moves for that piece as a vector<string>
}

int print_all_legal_moves_for_a_position(std::vector<std::vector<char>> &chess_board, char player_color, std::unordered_map<char, std::string> &chess_pieces)
{
    long long int total_moves = 0; // Stores the number of possible Move variations of every piece combined

    std::cout << "Printing all Legal Moves in the position piece by piece\n";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess_board[i][j] != '.' && player_color == 'W' && isupper(chess_board[i][j]))
            {
                std::vector<std::string> moves = generate_legal_moves_for_a_piece(chess_board, 'W', i, j); // Extracting Valid moves Per piece
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
                std::vector<std::string> moves = generate_legal_moves_for_a_piece(chess_board, 'B', i, j); // Extracting Valid moves Per piece
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
