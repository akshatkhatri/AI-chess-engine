#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <unordered_map>
#include<bits/stdc++.h>
using namespace std;

bool knight_attack(int i, int j, char king, vector<vector<char>> &board)
{
    cout << "Checking Knight Attack" << endl;
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
            cout << "Knight is attacking" << endl;
            return true;
        }
    }
    cout << "check complete knight not attacking" << endl;
    return false;
}

bool rook_queen_attack(int i, int j, char king, vector<vector<char>> &board)
{
    cout << "starting Rook Check" << endl;
    char rook = (king == 'W') ? 'r' : 'R';  // Opponent's rook
    char queen = (king == 'W') ? 'q' : 'Q'; // Opponent's queen
    cout<<"rook is "<<rook<<endl;
    cout<<"queen is "<<queen<<endl; 
    // Up
    for (int k = i - 1; k >= 0; k--)
    {
        if (board[k][j] != rook && board[k][j] != '.' && board[k][j] != queen)
            break;
        if (board[k][j] == rook || board[k][j] == queen)
        {
            cout << "Rook is attacking from Up" << endl;
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
            cout << "Rook is attacking from Down" << endl;
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
            cout << "Rook is attacking from Left" << endl;
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
            cout << "Rook is attacking from Right" << endl;
            return true;
        }
    }
    cout << "Check Complete ROok not attacking" << endl;
    return false;
}
bool bishop_queen_attack(int i, int j, char king, vector<vector<char>> &board)
{
    cout << "bishop_queen_check_started" << endl;
    char bishop = (king == 'W') ? 'b' : 'B';
    char queen = (king == 'W') ? 'q' : 'Q';
    // Up-Left
    for (int k = i - 1, p = j - 1; k >= 0 && p >= 0; k--, p--)
    {
        if (board[k][p] != bishop && board[k][p] != '.' && board[k][p] != queen)
            break;
        if (board[k][p] == bishop || board[k][p] == queen)
        {
            cout << "queen or bishop attacking from Up-left" << endl;
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
            cout << "queen or bishop attacking from Up-Right" << endl;
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
            cout << "queen or bishop attacking from Down-left" << endl;
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
            cout << "queen or bishop attacking from Down-Right" << endl;
            return true;
        }
    }
    cout << "Bishop Queen Check Complete" << endl;
    return false;
}

bool pawn_attack(int i, int j, char king, vector<vector<char>> &board)
{
    cout << "Pawn attack Check Started" << endl;
    char pawn = (king == 'W') ? 'p' : 'P';

    if (pawn == 'P')
    {
        if (i > 0)
        {
            if ((j > 0 && board[i - 1][j - 1] == pawn) || (j < 7 && board[i - 1][j + 1] == pawn))
            {
                cout << "Pawn(P) is attacking from diag" << endl;
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
                cout << "Pawn(p) is attacking from diag" << endl;
                return true;
            }
        }
    }
    cout << "Pawn Check Complete" << endl;
    return false;
}

bool king_in_check(vector<vector<char>> &chess_board, char turn_color)
{
    char king_to_check = turn_color;
    char king_symbol = (turn_color == 'W')?'K':'k';
    cout << "checking King with symbol " << king_symbol << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chess_board[i][j] == king_symbol)
            {
                cout << "king found at " << i << " " << j << endl;
                return knight_attack(i, j, king_to_check, chess_board) || rook_queen_attack(i, j, king_to_check, chess_board) || bishop_queen_attack(i, j, king_to_check, chess_board) || pawn_attack(i, j, king_to_check, chess_board);
            }
        }
    }
    return false;
}

bool check_piece_legality_and_move(vector<vector<char>> &chess_board, char piece, const string &move_start, const string move_dest)
{
    int start_i = move_start[0] - '0';
    int start_j = move_start[2] - '0';
    int dest_i = move_dest[0] - '0';
    int dest_j = move_dest[2] - '0';

    // Pawns Logic
    if (piece == 'P' || piece == 'p')
    {
        cout << "Checking pawn Validity" << endl;
        if (piece == 'P')
        {
            if (start_i <= dest_i)
            {
                cout << "pawns cannot be still or go backwards" << endl;
                return false;
            }
            if (start_i - dest_i > 2)
            {
                cout << "Pawns cannot move more than 2 spaces" << endl;
                return false;
            }
            if (start_i - dest_i == 2)
            {
                if (start_i != 6)
                {
                    cout << "pawns can only move two squares from starting Squares" << endl;
                    return false;
                }
            }
            if ((start_i == dest_i + 1 && start_j == dest_j - 1) || (start_i == dest_i + 1 && start_j == dest_j + 1)) // Capture Claimed
            {
                // Verifying Capture
                if (chess_board[dest_i][dest_j] == '.' || isupper(chess_board[dest_i][dest_j]))
                {
                    cout << "Capture not possible" << endl;
                    return false;
                }
                else
                {
                    char vacant_spot = chess_board[dest_i][dest_j];
                    chess_board[start_i][start_j] = '.';
                    chess_board[dest_i][dest_j] = 'P';

                    if (king_in_check(chess_board, 'W'))
                    {
                        cout << "White King is in Check , Current Move is Illegal" << endl;
                        chess_board[start_i][start_j] = 'P';
                        chess_board[dest_i][dest_j] = vacant_spot;
                        return false;
                    }
                    return true;
                }
            }
            if (dest_j == start_j)
            {
                // Checking no piece is blocking the path
                for (int i = start_i - 1; i >= dest_i; i--)
                {
                    if (chess_board[i][start_j] != '.')
                    {
                        cout << "Pawn is blocked" << endl;
                        return false;
                    }
                }
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'P';

                if (king_in_check(chess_board, 'W'))
                {
                    cout << "White King is in Check , Current Move is Illegal" << endl;
                    chess_board[start_i][start_j] = 'P';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }

                return true; // ✅ Valid normal move
            }

            cout << "Pawns cannot move horizontally" << endl;
            return false;
        }
        else // Checking for backwards moves and Captures with Black
        {
            if (start_i >= dest_i)
            {
                cout << "pawns cannot be still or go backwards" << endl;
                return false;
            }
            if (dest_i - start_i > 2)
            {
                cout << "Pawns cannot move more than 2 spaces" << endl;
                return false;
            }
            if (dest_i - start_i == 2)
            {
                if (start_i != 1)
                {
                    cout << "pawns can only move two squares from starting Squares" << endl;
                    return false;
                }
            }

            if ((start_i == dest_i - 1 && start_j == dest_j - 1) || (start_i == dest_i - 1 && start_j == dest_j + 1))
            {
                // Verifying Capture
                if (chess_board[dest_i][dest_j] == '.' || islower(chess_board[dest_i][dest_j])) // Must capture an enemy piece
                {
                    cout << "Capture not possible" << endl;
                    return false;
                }
                else
                {
                    char vacant_spot = chess_board[dest_i][dest_j];
                    chess_board[start_i][start_j] = '.';
                    chess_board[dest_i][dest_j] = 'p';

                    if (king_in_check(chess_board, 'B'))
                    {
                        cout << "Black King is in Check , Current Move is Illegal" << endl;
                        chess_board[start_i][start_j] = 'p';
                        chess_board[dest_i][dest_j] = vacant_spot;
                        return false;
                    }
                    return true;
                }
            }
            if (dest_j == start_j)
            {
                // Checking no piece is blocking the path
                for (int i = start_i + 1; i <= dest_i; i++)
                {
                    if (chess_board[i][start_j] != '.')
                    {
                        cout << "Pawn is blocked" << endl;
                        return false;
                    }
                }
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'p';

                if (king_in_check(chess_board, 'B'))
                {
                    cout << "Black King is in Check , Current Move is Illegal" << endl;
                    chess_board[start_i][start_j] = 'p';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                return true; // ✅ Valid normal move
            }

            cout << "Pawns cannot move horizontally" << endl;
            return false;
        }
    }
    // Rooks Logic
    if (piece == 'R' || piece == 'r')
    {
        if (start_i != dest_i && start_j != dest_j)
        {
            cout << "Rooks Dont move this way" << endl;
            return false;
        }
        if (start_i == dest_i && dest_j > start_j) // moving horizontally Right
        {
            // right
            for (int j = start_j + 1; j < dest_j; j++)
            {
                if (chess_board[start_i][j] != '.')
                {
                    cout << "Rook cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }
        if (start_i == dest_i && dest_j < start_j) // Moving Horizontally Left
        {
            // Left
            for (int j = start_j - 1; j > dest_j; j--)
            {
                if (chess_board[start_i][j] != '.')
                {
                    cout << "Rook cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }
        if (start_j == dest_j && dest_i > start_i) // Moving Vertically down
        {
            for (int i = start_i + 1; i < dest_i; i++)
            {
                if (chess_board[i][start_j] != '.')
                {
                    cout << "Rook cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }
        if (start_j == dest_j && dest_i < start_i)
        {
            for (int i = start_i - 1; i > dest_i; i--) // Moving Vertically Up
            {
                if (chess_board[i][start_j] != '.')
                {
                    cout << "Rook cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }

        if (piece == 'R')
        {
            if (chess_board[dest_i][dest_j] == '.' || islower(chess_board[dest_i][dest_j]))
            {
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'R';

                if (king_in_check(chess_board, 'W'))
                {
                    cout << "White King is in Check , Current Move is Illegal" << endl;
                    chess_board[start_i][start_j] = 'R';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }

                return true;
            }
            else
            {
                cout << "Friendly Peace is on Destination" << endl;
                return false;
            }
        }
        else
        {
            if (chess_board[dest_i][dest_j] == '.' || isupper(chess_board[dest_i][dest_j]))
            {
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'r';

                if (king_in_check(chess_board, 'B'))
                {
                    cout << "Black King is in Check , Current Move is Illegal" << endl;
                    chess_board[start_i][start_j] = 'r';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                return true;
            }
            else
            {
                cout << "Friendly Peace is on Destination" << endl;
                return false;
            }
        }
        return true;
    }
    // Bishop Logic
    if (piece == 'B' || piece == 'b')
    {
        if (abs(dest_i - start_i) != abs(dest_j - start_j))
        {
            return false; // Not a valid diagonal move
        }
        /*
        Why does abs(dest_i - start_i) == abs(dest_j - start_j) ensure diagonal movement?
        Bishops move diagonally:
        This means they move the same number of squares vertically (i change) as they do horizontally (j change).
        If a bishop moves X rows up or down, it must also move X columns left or right.
        Mathematical Representation:

        If the piece starts at (start_i, start_j) and moves to (dest_i, dest_j), the total movement is:
        abs(dest_i - start_i): Change in row (vertical movement)
        abs(dest_j - start_j): Change in column (horizontal movement)
        For diagonal movement, these two must be equal.
        */
        if (dest_i < start_i && dest_j < start_j) // Up-left
        {
            for (int k = start_i - 1, p = start_j - 1; k > dest_i && p > dest_j; k--, p--)
            {
                if (chess_board[k][p] != '.')
                {
                    cout << "Bishop cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }
        if (dest_i < start_i && dest_j > start_j) // up-right
        {
            for (int k = start_i - 1, p = start_j + 1; k > dest_i && p < dest_j; k--, p++)
            {
                if (chess_board[k][p] != '.')
                {
                    cout << "Bishop cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }

        if (dest_i > start_i && dest_j < start_j) // Down-left
        {
            for (int k = start_i + 1, p = start_j - 1; k < dest_i && p > dest_j; k++, p--)
            {
                if (chess_board[k][p] != '.')
                {
                    cout << "Bishop cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }

        if (dest_i > start_i && dest_j > start_j) // Down-Right
        {
            for (int k = start_i + 1, p = start_j + 1; k < dest_i && p < dest_j; k++, p++)
            {
                if (chess_board[k][p] != '.')
                {
                    cout << "Bishop cannot move there , Another piece is in the way" << endl;
                    return false;
                }
            }
        }

        if (piece == 'B')
        {
            if (chess_board[dest_i][dest_j] == '.' || islower(chess_board[dest_i][dest_j]))
            {
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'B';

                if (king_in_check(chess_board, 'W'))
                {
                    cout << "White King is in Check , Current Move is Illegal" << endl;
                    chess_board[start_i][start_j] = 'B';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                return true;
            }
            else
            {
                cout << "Friendly Piece is on Destination" << endl;
                return false;
            }
        }
        else
        {
            if (chess_board[dest_i][dest_j] == '.' || isupper(chess_board[dest_i][dest_j]))
            {
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'b';

                if (king_in_check(chess_board, 'B'))
                {
                    cout << "White King is in Check , Current Move is Illegal" << endl;
                    chess_board[start_i][start_j] = 'b';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                return true;
            }
            else
            {
                cout << "Friendly Piece is on Destination" << endl;
                return false;
            }
        }

        return true;
    }
    // Queen Logic
    if (piece == 'Q' || piece == 'q')
    {
        // Checking if the Queen moves like a Bishop
        if (abs(start_i - dest_i) == abs(start_j - dest_j))
        {
            int row_dir = (dest_i > start_i) ? 1 : -1;
            int col_dir = (dest_j > start_j) ? 1 : -1;

            for (int i = start_i + row_dir, j = start_j + col_dir; i != dest_i; i += row_dir, j += col_dir)
            {
                if (chess_board[i][j] != '.')
                {
                    cout << "Queen is blocked (Diagonal)" << endl;
                    return false;
                }
            }
        }
        // Checking if the Queen moves like a Rook
        else if (start_i == dest_i || start_j == dest_j)
        {
            if (start_i == dest_i) // Moving horizontally
            {
                int dir = (dest_j > start_j) ? 1 : -1;
                for (int j = start_j + dir; j != dest_j; j += dir)
                {
                    if (chess_board[start_i][j] != '.')
                    {
                        cout << "Queen is blocked (Horizontal)" << endl;
                        return false;
                    }
                }
            }
            else // Moving vertically
            {
                int dir = (dest_i > start_i) ? 1 : -1;
                for (int i = start_i + dir; i != dest_i; i += dir)
                {
                    if (chess_board[i][start_j] != '.')
                    {
                        cout << "Queen is blocked (Vertical)" << endl;
                        return false;
                    }
                }
            }
        }
        else
        {
            cout << "Queen must move diagonally or straight" << endl;
            return false;
        }

        // Capture verification
        if (chess_board[dest_i][dest_j] != '.' &&
            ((piece == 'Q' && isupper(chess_board[dest_i][dest_j])) || (piece == 'q' && islower(chess_board[dest_i][dest_j]))))
        {
            cout << "Queen cannot capture its own piece" << endl;
            return false;
        }

        // Simulate the move and check if the king is in check
        char vacant_spot = chess_board[dest_i][dest_j];
        chess_board[start_i][start_j] = '.';
        chess_board[dest_i][dest_j] = piece;

        if (king_in_check(chess_board, (piece == 'Q') ? 'W' : 'B'))
        {
            cout << "Move puts King in check, illegal move!" << endl;
            chess_board[start_i][start_j] = piece;
            chess_board[dest_i][dest_j] = vacant_spot;
            return false;
        }

        return true; // ✅ Valid move
    }
    // Knight Logic
    if (piece == 'N' || piece == 'n')
    {
        int row_diff = abs(start_i - dest_i);
        int col_diff = abs(start_j - dest_j);

        // Valid Knight Move Check (L-shape)
        if (!((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)))
        {
            cout << "Invalid knight move!" << endl;
            return false;
        }

        // Capture Verification
        if (chess_board[dest_i][dest_j] != '.' &&
            ((piece == 'N' && isupper(chess_board[dest_i][dest_j])) ||
             (piece == 'n' && islower(chess_board[dest_i][dest_j]))))
        {
            cout << "Knight cannot capture its own piece!" << endl;
            return false;
        }

        // Simulate the move and check if the king is in check
        char vacant_spot = chess_board[dest_i][dest_j];
        chess_board[start_i][start_j] = '.';
        chess_board[dest_i][dest_j] = piece;

        if (king_in_check(chess_board, (piece == 'N') ? 'W' : 'B'))
        {
            cout << "Move puts King in check, illegal move!" << endl;
            chess_board[start_i][start_j] = piece;
            chess_board[dest_i][dest_j] = vacant_spot;
            return false;
        }

        return true; // ✅ Valid knight move
    }
    // King's Logic
    if (piece == 'K' || piece == 'k')
    {
        int row_diff = abs(start_i - dest_i);
        int col_diff = abs(start_j - dest_j);

        // King can only move one step in any direction
        if (row_diff > 1 || col_diff > 1)
        {
            cout << "King can only move one square!" << endl;
            return false;
        }

        // Capture Verification
        if (chess_board[dest_i][dest_j] != '.' &&
            ((piece == 'K' && isupper(chess_board[dest_i][dest_j])) ||
             (piece == 'k' && islower(chess_board[dest_i][dest_j]))))
        {
            cout << "King cannot capture its own piece!" << endl;
            return false;
        }

        // Simulate the move and check if the king is in check
        char vacant_spot = chess_board[dest_i][dest_j];
        chess_board[start_i][start_j] = '.';
        chess_board[dest_i][dest_j] = piece;

        if (king_in_check(chess_board, (piece == 'K') ? 'W' : 'B'))
        {
            cout << "Move puts King in check, illegal move!" << endl;
            chess_board[start_i][start_j] = piece;
            chess_board[dest_i][dest_j] = vacant_spot;
            return false;
        }

        return true; // ✅ Valid move
    }

    cout << "something bad occured" << endl;
    return false;
}

// e4 d5 exd5 Nf6 Bb5+ O-O O-O-O h8=Q Nxe5 cxd6 e.p. R1d3 Qg5#
bool move_is_legal(vector<vector<char>> &chess_board, const string &move_start, const string move_dest, char player_color)
{
    cout << "Checking legality: " << move_start << " to " << move_dest << endl;
    // Input to be received in format 6,4 to 4,4 for white or 1,4 to 3,4 for black
    if (move_start.size() != 3 || move_dest.size() != 3)
    {
        cout << "invalid input format length , input should be size 3 in format 6,4  OR  2,4   e.t.c." << endl;
        return false;
    }

    if (move_start[0] < '0' || move_start[0] > '7' || move_start[2] < '0' || move_start[2] > '7')
    {
        cout << "Start Move input out of bounds (must be between 0 and 7)" << endl;
        return false;
    }
    if (move_dest[0] < '0' || move_dest[0] > '7' || move_dest[2] < '0' || move_dest[2] > '7')
    {
        cout << "Destination Move input out of bounds (must be between 0 and 7)" << endl;
        return false;
    }

    int start_row = move_start[0] - '0'; // Convert character to integer
    int start_col = move_start[2] - '0';

    int dest_row = move_dest[0] - '0';
    int dest_col = move_dest[2] - '0';

    char piece_to_move = chess_board[start_row][start_col];
    if (move_start == move_dest)
    {
        cout << "Starting and Destination cannot be the same" << endl; // TO-DO
        return false;
    }
    if (piece_to_move == '.')
    {
        cout << "Invalid Move , Select A square with a piece" << endl; // Handling Errors TO-DO
        return false;
    }
    if (player_color == 'W' && islower(piece_to_move))
    {
        cout << "Invalid Move Select Your own piece" << endl;
        return false;
    }
    if (player_color == 'B' && isupper(piece_to_move))
    {
        cout << "Invalid Move select your own piece" << endl;
        return false;
    }
    cout << "Checking Piece Legality and Move" << endl;
    if (check_piece_legality_and_move(chess_board, piece_to_move, move_start, move_dest))
    {
        cout << "THe move is Valid ... Updating Board...." << endl;
        return true;
    }
    else
    {
        cout << "The move is Illegal.. Try again" << endl;
    }
    return false;
}
void display_board(vector<vector<char>> &chess_board,unordered_map<char, string>&chess_pieces)
{
    cout << "\n        0         1         2         3         4         5         6         7  \n";
    cout << "    --------------------------------------------------------------------------------\n";
    for (int i = 0; i < 8; i++)
    {
        cout << i << "  |"; // Row label
        for (int j = 0; j < 8; j++)
        {
            if(chess_board[i][j]!='.')
                cout << "    " << chess_pieces[chess_board[i][j]] << "    |"; // Extra spaces for width
            else
                cout<< "    "<<chess_board[i][j]<< "    |";
        }
        cout << "  " << i; // Right-side row label
        cout << "\n    --------------------------------------------------------------------------------\n";
    }
    cout << "        0         1         2         3         4         5         6         7  \n";
}


int main()
{
    SetConsoleOutputCP(65001);
    cout<<"♜   ♞"<<endl;
    vector<vector<char>> chess_board = {
        //    0    1    2    3    4    5    6    7
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // 0
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // 1
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 2
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 3
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 4
        {'.', '.', '.', '.', '.', '.', '.', '.'}, // 5
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 6
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // 7
    };
    cout << "=========================================\n";
    cout << "       Welcome to Player vs Player Chess \n";
    cout << "=========================================\n\n";
    cout << ">> Enter your moves in the format: row,col (e.g., 6,4)\n";
    cout << ">> Rows and columns are indexed from 0 to 7\n";
    cout << ">> First, pick the piece you want to move.\n";
    cout << ">> Then, enter the destination where you want to move it.\n";
    cout << ">> If the move is legal, we will execute it.\n";
    cout << ">> Type 'exit' to quit the game\n";
    cout << ">> Have fun and play fair!\n";
    cout << "-----------------------------------------\n";

    unordered_map<char, string> chess_pieces = {
        {'P', "♙"}, {'p', "♟"},  // White Pawn, Black Pawn
        {'R', "♖"}, {'r', "♜"},  // White Rook, Black Rook
        {'N', "♘"}, {'n', "♞"},  // White Knight, Black Knight
        {'B', "♗"}, {'b', "♝"},  // White Bishop, Black Bishop
        {'Q', "♕"}, {'q', "♛"},  // White Queen, Black Queen
        {'K', "♔"}, {'k', "♚"}   // White King, Black King
    };

    while (true) // Infinite loop until game ends
    {
        string move_start, move_dest;

        // **White's Turn**
        while (true)
        {
            display_board(chess_board,chess_pieces);
            cout << "\n♔ White's Turn: Pick the piece you want to move (Format: row,col or 'exit' to quit/Resign): ";
            cin >> move_start;
            if (move_start == "exit")
            {
                cout << "WHite Resigned" << endl;
                return 0; // Exit condition
            }
            cout << "♔ White's Turn: Pick the destination (Format: row,col): ";
            cin >> move_dest;
            if (move_dest == "exit")
            {
                cout << "white resigned" << endl;
                return 0; // Exit condition
            }
            if (move_is_legal(chess_board, move_start, move_dest, 'W'))
            {
                cout << "✅ White's move executed successfully!\n";
                break; // Move was legal, break out of loop
            }
            cout << "⚠️  Illegal move! Try again.\n";
        }

        // **Black's Turn**
        while (true)
        {
            display_board(chess_board,chess_pieces);

            cout << "\n♚ Black's Turn: Pick the piece you want to move (Format: row,col or 'exit' to quit): ";
            cin >> move_start;
            if (move_start == "exit")
            {
                cout << "Black Resigned" << endl;
                return 0;
            }
            cout << "♚ Black's Turn: Pick the destination (Format: row,col): ";
            cin >> move_dest;
            if (move_dest == "exit")
            {
                cout << "Black Resigned !" << endl;
                return 0;
            }
            if (move_is_legal(chess_board, move_start, move_dest, 'B'))
            {
                cout << "✅ Black's move executed successfully!\n";
                break; // Move was legal, break out of loop
            }
            cout << "⚠️  Illegal move! Try again.\n";
        }
    }

    return 0;
}