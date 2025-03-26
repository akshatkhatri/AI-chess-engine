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

bool pawn_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    char pawn = (king == 'W') ? 'p' : 'P';

    if (pawn == 'P')
    {
        if (i > 0)
        {
            if ((j > 0 && board[i - 1][j - 1] == pawn) || (j < 7 && board[i - 1][j + 1] == pawn))
            {
                return true;
            }
        }
    }
    else
    {
        if (i < 7)
        {
            if ((j > 0 && board[i + 1][j - 1] == pawn) || (j < 7 && board[i + 1][j + 1] == pawn))
            {
                return true;
            }
        }
    }
    return false;
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
                return knight_attack(i, j, king_to_check, chess_board) || rook_queen_attack(i, j, king_to_check, chess_board) || bishop_queen_attack(i, j, king_to_check, chess_board) || pawn_attack(i, j, king_to_check, chess_board);
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
