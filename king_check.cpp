#include "king_check.h"
#include <iostream>
#include <vector>
#include<string>

bool knight_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    std::cout << "Checking Knight Attack" << std::endl;
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
            std::cout << "Knight is attacking" << std::endl;
            return true;
        }
    }
    std::cout << "check complete knight not attacking" << std::endl;
    return false;
}

bool rook_queen_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    std::cout << "starting Rook Check" << std::endl;
    char rook = (king == 'W') ? 'r' : 'R';  // Opponent's rook
    char queen = (king == 'W') ? 'q' : 'Q'; // Opponent's queen
    std::cout << "rook is " << rook << std::endl;
    std::cout << "queen is " << queen << std::endl;
    // Up
    for (int k = i - 1; k >= 0; k--)
    {
        if (board[k][j] != rook && board[k][j] != '.' && board[k][j] != queen)
            break;
        if (board[k][j] == rook || board[k][j] == queen)
        {
            std::cout << "Rook is attacking from Up" << std::endl;
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
            std::cout << "Rook is attacking from Down" << std::endl;
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
            std::cout << "Rook is attacking from Left" << std::endl;
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
            std::cout << "Rook is attacking from Right" << std::endl;
            return true;
        }
    }
    std::cout << "Check Complete ROok not attacking" << std::endl;
    return false;
}

bool bishop_queen_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    std::cout << "bishop_queen_check_started" << std::endl;
    char bishop = (king == 'W') ? 'b' : 'B';
    char queen = (king == 'W') ? 'q' : 'Q';
    // Up-Left
    for (int k = i - 1, p = j - 1; k >= 0 && p >= 0; k--, p--)
    {
        if (board[k][p] != bishop && board[k][p] != '.' && board[k][p] != queen)
            break;
        if (board[k][p] == bishop || board[k][p] == queen)
        {
            std::cout << "queen or bishop attacking from Up-left" << std::endl;
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
            std::cout << "queen or bishop attacking from Up-Right" << std::endl;
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
            std::cout << "queen or bishop attacking from Down-left" << std::endl;
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
            std::cout << "queen or bishop attacking from Down-Right" << std::endl;
            return true;
        }
    }
    std::cout << "Bishop Queen Check Complete" << std::endl;
    return false;
}

bool pawn_attack(int i, int j, char king, std::vector<std::vector<char>> &board)
{
    std::cout << "Pawn attack Check Started" << std::endl;
    char pawn = (king == 'W') ? 'p' : 'P';

    if (pawn == 'P')
    {
        if (i > 0)
        {
            if ((j > 0 && board[i - 1][j - 1] == pawn) || (j < 7 && board[i - 1][j + 1] == pawn))
            {
                std::cout << "Pawn(P) is attacking from diag" << std::endl;
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
                std::cout << "Pawn(p) is attacking from diag" << std::endl;
                return true;
            }
        }
    }
    std::cout << "Pawn Check Complete" << std::endl;
    return false;
}

bool king_in_check(std::vector<std::vector<char>> &chess_board, char turn_color)
{
    char king_to_check = turn_color;
    char king_symbol = (turn_color == 'W') ? 'K' : 'k';
    std::cout << "checking King with symbol " << king_symbol << std::endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess_board[i][j] == king_symbol)
            {
                std::cout << "king found at " << i << " " << j << std::endl;
                return knight_attack(i, j, king_to_check, chess_board) || rook_queen_attack(i, j, king_to_check, chess_board) || bishop_queen_attack(i, j, king_to_check, chess_board) || pawn_attack(i, j, king_to_check, chess_board);
            }
        }
    }
    return false;
}

