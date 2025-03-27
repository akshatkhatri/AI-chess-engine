#include "king_check.h"
#include <iostream>
#include <vector>
#include<string>

bool knight_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    char knight = (king == 'W') ? 'n' : 'N';

    // Possible knight moves (8 directions)
    int moves[8][2] = {
        {-2, -1}, {-2, 1}, // Up-Left, Up-Right
        {2, -1},
        {2, 1}, // Down-Left, Down-Right
        {-1, -2},
        {-1, 2}, // Left-Up, Left-Down
        {1, -2},
        {1, 2} // Right-Up, Right-Down
    };

    for (int k = 0; k < 8; k++)
    {
        int ni = i + moves[k][0];
        int nj = j + moves[k][1];

        if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8 && board[ni][nj] == knight)
        {
            return true;
        }
    }
    return false;
}

bool rook_queen_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    char rook = (king == 'W') ? 'r' : 'R';  // Opponent's rook
    char queen = (king == 'W') ? 'q' : 'Q'; // Opponent's queen

    // Up
    for (int k = i - 1; k >= 0; k--)
    {
        if (board[k][j] != rook && board[k][j] != '.' && board[k][j] != queen)
            break;
        if (board[k][j] == rook || board[k][j] == queen)
        {
            return true;
        }
    }
    // Down
    for (int k = i + 1; k < 8; k++)
    {
        if (board[k][j] != rook && board[k][j] != '.' && board[k][j] != queen)
            break;
        if (board[k][j] == rook || board[k][j] == queen)
        {
            return true;
        }
    }
    // Left
    for (int k = j - 1; k >= 0; k--)
    {
        if (board[i][k] != rook && board[i][k] != '.' && board[i][k] != queen)
            break;
        if (board[i][k] == rook || board[i][k] == queen)
        {
            return true;
        }
    }
    // Right
    for (int k = j + 1; k < 8; k++)
    {
        if (board[i][k] != rook && board[i][k] != '.' && board[i][k] != queen)
            break;
        if (board[i][k] == rook || board[i][k] == queen)
        {
            return true;
        }
    }
    return false;
}

bool bishop_queen_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    char bishop = (king == 'W') ? 'b' : 'B';
    char queen = (king == 'W') ? 'q' : 'Q';
    // Up-Left
    for (int k = i - 1, p = j - 1; k >= 0 && p >= 0; k--, p--)
    {
        if (board[k][p] != bishop && board[k][p] != '.' && board[k][p] != queen)
            break;
        if (board[k][p] == bishop || board[k][p] == queen)
        {
            return true;
        }
    }

    // Up-right
    for (int k = i - 1, p = j + 1; k >= 0 && p < 8; k--, p++)
    {
        if (board[k][p] != bishop && board[k][p] != '.' && board[k][p] != queen)
            break;
        if (board[k][p] == bishop || board[k][p] == queen)
        {
            return true;
        }
    }

    // Down-left
    for (int k = i + 1, p = j - 1; k < 8 && p >= 0; k++, p--)
    {
        if (board[k][p] != bishop && board[k][p] != '.' && board[k][p] != queen)
            break;
        if (board[k][p] == bishop || board[k][p] == queen)
        {
            return true;
        }
    }
    // Down-Right
    for (int k = i + 1, p = j + 1; k < 8 && p < 8; k++, p++)
    {
        if (board[k][p] != bishop && board[k][p] != '.' && board[k][p] != queen)
            break;
        if (board[k][p] == bishop || board[k][p] == queen)
        {
            return true;
        }
    }
    return false;
}

bool pawn_attack(int i, int j, char king, std::vector<std::vector<char>> &board) {
    // Determine the enemy pawn
    char enemy_pawn = (king == 'W') ? 'p' : 'P';
    
    // Direction of attack: Black pawns move up (-1), White pawns move down (+1)
    int direction = (enemy_pawn == 'p') ? -1 : 1; 
    
    int new_i = i + direction; // Row where pawn attacks

    // Check if within board limits
    if (new_i >= 0 && new_i < 8) {
        if ((j > 0 && board[new_i][j - 1] == enemy_pawn) || 
            (j < 7 && board[new_i][j + 1] == enemy_pawn)) {
            return true; // King is under attack
        }
    }
    
    return false; // No attack found
}


//Logically this thing is never true but when generating moves , we have to check this

bool king_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    char opp_king = (king == 'W') ? 'k' : 'K';

    // Possible king moves (one step in all 8 directions)
    int moves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Top-left, Top, Top-right
        {0, -1},          {0, 1},   // Left, Right
        {1, -1}, {1, 0}, {1, 1}     // Bottom-left, Bottom, Bottom-right
    };

    for (int k = 0; k < 8; k++)
    {
        int new_i = i + moves[k][0];
        int new_j = j + moves[k][1];

        // Check if within bounds
        if (new_i >= 0 && new_i < 8 && new_j >= 0 && new_j < 8)
        {
            // Check if the opponent's king is in an adjacent square
            if (board[new_i][new_j] == opp_king)
            {
                return true; // The king is under attack
            }
        }
    }
    return false; // The king is not under attack by the opponent's king
}


bool king_in_check(std::vector<std::vector<char>> &chess_board, char turn_color)
{
    char king_to_check = turn_color;
    char king_symbol = (turn_color == 'W') ? 'K' : 'k';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess_board[i][j] == king_symbol)
            {
                return knight_attack(i, j, king_to_check, chess_board) || rook_queen_attack(i, j, king_to_check, chess_board) || bishop_queen_attack(i, j, king_to_check, chess_board) || pawn_attack(i, j, king_to_check, chess_board) || king_attack(i,j,king_to_check,chess_board);
            }
        }
    }
    return false;
}

bool is_legal_after_move(std::vector<std::vector<char>> &chess_board, int start_row, int start_col, int end_row, int end_col, char player_color)
{
    // Get the piece from the board
    char piece = chess_board[start_row][start_col];

    // Store the original piece at the destination
    char temp = chess_board[end_row][end_col];

    // Simulate the move
    chess_board[end_row][end_col] = piece;
    chess_board[start_row][start_col] = '.';

    // Check if the move results in check
    bool legal = !king_in_check(chess_board, player_color);

    // Undo the move
    chess_board[start_row][start_col] = piece;
    chess_board[end_row][end_col] = temp;

    return legal;
}
