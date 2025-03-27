#include "movement.h"
#include "chessboard.h"
#include "king_check.h"
#include "legalmoves.h"
#include "notations.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

bool check_piece_legality_and_move(std::vector<std::vector<char>> &chess_board, char piece, const std::string &player_move_start, const std::string player_move_dest, const std::string opponent_move_start, const std::string opponent_move_dest, bool &player_king_moved, bool &king_side_rook_moved, bool &queen_side_rook_moved)
{
    int start_i = player_move_start[0] - '0';
    int start_j = player_move_start[2] - '0';
    int dest_i = player_move_dest[0] - '0';
    int dest_j = player_move_dest[2] - '0';

    int opp_start_i;
    int opp_start_j;
    int opp_dest_i;
    int opp_dest_j;

    if (!opponent_move_start.empty())
    {
        opp_start_i = opponent_move_start[0] - '0';
        opp_start_j = opponent_move_start[2] - '0';
        opp_dest_i = opponent_move_dest[0] - '0';
        opp_dest_j = opponent_move_dest[2] - '0';
    }

    // Pawns Logic
    if (piece == 'P' || piece == 'p')
    {
        std::cout << "Checking pawn Validity" << std::endl;
        if (piece == 'P')
        {
            if (start_i <= dest_i)
            {
                std::cout << "pawns cannot be still or go backwards" << std::endl;
                return false;
            }
            if (start_i - dest_i > 2)
            {
                std::cout << "Pawns cannot move more than 2 spaces" << std::endl;
                return false;
            }
            if (start_i - dest_i == 2)
            {
                if (start_i != 6)
                {
                    std::cout << "pawns can only move two squares from starting Squares" << std::endl;
                    return false;
                }
            }
            if ((start_i == dest_i + 1 && start_j == dest_j - 1) || (start_i == dest_i + 1 && start_j == dest_j + 1)) // Capture Claimed
            {
                // Verifying Special Capture (En-Passant)
                std::cout << "Checking For En-Passant" << std::endl;
                if (!opponent_move_start.empty() && chess_board[opp_dest_i][opp_dest_j] == 'p' && opp_start_i == 1 && opp_dest_i == 3 && dest_j == opp_dest_j && start_i == 3)
                {
                    char vacant_spot = chess_board[dest_i][dest_j];
                    chess_board[start_i][start_j] = '.';
                    chess_board[dest_i][dest_j] = 'P';
                    chess_board[opp_dest_i][opp_dest_j] = '.';

                    if (king_in_check(chess_board, 'W'))
                    {
                        std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                        chess_board[start_i][start_j] = 'P';
                        chess_board[dest_i][dest_j] = vacant_spot;
                        chess_board[opp_dest_i][opp_dest_j] = 'p';
                        return false;
                    }
                    std::cout << "En-Passant Move Executed" << std::endl;
                    return true;
                }

                // Verifying Simple Capture
                if (chess_board[dest_i][dest_j] == '.' || isupper(chess_board[dest_i][dest_j]))
                {
                    std::cout << "Capture not possible" << std::endl;
                    return false;
                }
                else
                {
                    char vacant_spot = chess_board[dest_i][dest_j];
                    chess_board[start_i][start_j] = '.';
                    chess_board[dest_i][dest_j] = 'P';

                    if (king_in_check(chess_board, 'W'))
                    {
                        std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                        chess_board[start_i][start_j] = 'P';
                        chess_board[dest_i][dest_j] = vacant_spot;
                        return false;
                    }
                    if (dest_i == 0) // Checking FOr pawn Promotion
                    {
                        std::cout << "Promotion Claimed" << std::endl;
                        std::cout << "Select the piece you want to promote to (Q, R, B, N): ";
                        char promotion_piece;
                        std::cin >> promotion_piece;
                        if (promotion_piece != 'Q' && promotion_piece != 'R' && promotion_piece != 'B' && promotion_piece != 'N')
                        {
                            std::cout << "Invalid promotion piece!" << std::endl;
                            return false;
                        }
                        chess_board[dest_i][dest_j] = promotion_piece;
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
                        std::cout << "Pawn is blocked" << std::endl;
                        return false;
                    }
                }
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'P';

                if (king_in_check(chess_board, 'W'))
                {
                    std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                    chess_board[start_i][start_j] = 'P';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                if (dest_i == 0) // Checking For Pawn Promotion
                {
                    std::cout << "Promotion Claimed" << std::endl;
                    std::cout << "Select the piece you want to promote to (Q, R, B, N): ";
                    char promotion_piece;
                    std::cin >> promotion_piece;
                    if (promotion_piece != 'Q' && promotion_piece != 'R' && promotion_piece != 'B' && promotion_piece != 'N')
                    {
                        std::cout << "Invalid promotion piece!" << std::endl;
                        return false;
                    }
                    chess_board[dest_i][dest_j] = promotion_piece;
                }
                return true; // ✅ Valid normal move
            }

            std::cout << "Pawns cannot move horizontally" << std::endl;
            return false;
        }
        else // Checking for backwards moves and Captures with Black
        {
            if (start_i >= dest_i)
            {
                std::cout << "pawns cannot be still or go backwards" << std::endl;
                return false;
            }
            if (dest_i - start_i > 2)
            {
                std::cout << "Pawns cannot move more than 2 spaces" << std::endl;
                return false;
            }
            if (dest_i - start_i == 2)
            {
                if (start_i != 1)
                {
                    std::cout << "pawns can only move two squares from starting Squares" << std::endl;
                    return false;
                }
            }

            if ((start_i == dest_i - 1 && start_j == dest_j - 1) || (start_i == dest_i - 1 && start_j == dest_j + 1))
            {
                // Verifying Special Capture (En-Passant)
                std::cout << "Checking For En-Passant" << std::endl;
                if (!opponent_move_start.empty() && chess_board[opp_dest_i][opp_dest_j] == 'P' && opp_start_i == 6 && opp_dest_i == 4 && dest_j == opp_dest_j && start_i == 4)
                {
                    char vacant_spot = chess_board[dest_i][dest_j];
                    chess_board[start_i][start_j] = '.';
                    chess_board[dest_i][dest_j] = 'p';
                    chess_board[opp_dest_i][opp_dest_j] = '.';

                    if (king_in_check(chess_board, 'W'))
                    {
                        std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                        chess_board[start_i][start_j] = 'P';
                        chess_board[dest_i][dest_j] = vacant_spot;
                        chess_board[opp_dest_i][opp_dest_j] = 'p';
                        return false;
                    }
                    std::cout << "En-Passant Move Executed" << std::endl;
                    return true;
                }

                // Verifying Capture
                if (chess_board[dest_i][dest_j] == '.' || islower(chess_board[dest_i][dest_j])) // Must capture an enemy piece
                {
                    std::cout << "Capture not possible" << std::endl;
                    return false;
                }
                else
                {
                    char vacant_spot = chess_board[dest_i][dest_j];
                    chess_board[start_i][start_j] = '.';
                    chess_board[dest_i][dest_j] = 'p';

                    if (king_in_check(chess_board, 'B'))
                    {
                        std::cout << "Black King is in Check , Current Move is Illegal" << std::endl;
                        chess_board[start_i][start_j] = 'p';
                        chess_board[dest_i][dest_j] = vacant_spot;
                        return false;
                    }
                    if (dest_i == 7)
                    {
                        std::cout << "Promotion Claimed" << std::endl;
                        std::cout << "Select the piece you want to promote to (q, r, b, n): ";
                        char promotion_piece;
                        std::cin >> promotion_piece;
                        if (promotion_piece != 'q' && promotion_piece != 'r' && promotion_piece != 'b' && promotion_piece != 'n')
                        {
                            std::cout << "Invalid promotion piece!" << std::endl;
                            return false;
                        }
                        chess_board[dest_i][dest_j] = promotion_piece;
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
                        std::cout << "Pawn is blocked" << std::endl;
                        return false;
                    }
                }
                char vacant_spot = chess_board[dest_i][dest_j];
                chess_board[start_i][start_j] = '.';
                chess_board[dest_i][dest_j] = 'p';

                if (king_in_check(chess_board, 'B'))
                {
                    std::cout << "Black King is in Check , Current Move is Illegal" << std::endl;
                    chess_board[start_i][start_j] = 'p';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                if (dest_i == 7)
                {
                    std::cout << "Promotion Claimed" << std::endl;
                    std::cout << "Select the piece you want to promote to (q, r, b, n): ";
                    char promotion_piece;
                    std::cin >> promotion_piece;
                    if (promotion_piece != 'q' && promotion_piece != 'r' && promotion_piece != 'b' && promotion_piece != 'n')
                    {
                        std::cout << "Invalid promotion piece!" << std::endl;
                        return false;
                    }
                    chess_board[dest_i][dest_j] = promotion_piece;
                }
                return true; // ✅ Valid normal move
            }

            std::cout << "Pawns cannot move horizontally" << std::endl;
            return false;
        }
    }
    // Rooks Logic
    if (piece == 'R' || piece == 'r')
    {
        if (start_i != dest_i && start_j != dest_j)
        {
            std::cout << "Rooks Dont move this way" << std::endl;
            return false;
        }
        if (start_i == dest_i && dest_j > start_j) // moving horizontally Right
        {
            // right
            for (int j = start_j + 1; j < dest_j; j++)
            {
                if (chess_board[start_i][j] != '.')
                {
                    std::cout << "Rook cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "Rook cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "Rook cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "Rook cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                    chess_board[start_i][start_j] = 'R';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                start_j == 7 ? king_side_rook_moved = true : queen_side_rook_moved = true;
                std::cout << "White King side rook moved? " << king_side_rook_moved << std::endl;
                return true;
            }
            else
            {
                std::cout << "Friendly Peace is on Destination" << std::endl;
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
                    std::cout << "Black King is in Check , Current Move is Illegal" << std::endl;
                    chess_board[start_i][start_j] = 'r';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                start_j == 7 ? king_side_rook_moved = true : queen_side_rook_moved = true;
                std::cout << "Black King side rook moved? " << king_side_rook_moved << std::endl;
                return true;
            }
            else
            {
                std::cout << "Friendly Peace is on Destination" << std::endl;
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
                    std::cout << "Bishop cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "Bishop cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "Bishop cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "Bishop cannot move there , Another piece is in the way" << std::endl;
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
                    std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                    chess_board[start_i][start_j] = 'B';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                return true;
            }
            else
            {
                std::cout << "Fristd::endly Piece is on Destination" << std::endl;
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
                    std::cout << "White King is in Check , Current Move is Illegal" << std::endl;
                    chess_board[start_i][start_j] = 'b';
                    chess_board[dest_i][dest_j] = vacant_spot;
                    return false;
                }
                return true;
            }
            else
            {
                std::cout << "Fristd::endly Piece is on Destination" << std::endl;
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
                    std::cout << "Queen is blocked (Diagonal)" << std::endl;
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
                        std::cout << "Queen is blocked (Horizontal)" << std::endl;
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
                        std::cout << "Queen is blocked (Vertical)" << std::endl;
                        return false;
                    }
                }
            }
        }
        else
        {
            std::cout << "Queen must move diagonally or straight" << std::endl;
            return false;
        }

        // Capture verification
        if (chess_board[dest_i][dest_j] != '.' &&
            ((piece == 'Q' && isupper(chess_board[dest_i][dest_j])) || (piece == 'q' && islower(chess_board[dest_i][dest_j]))))
        {
            std::cout << "Queen cannot capture its own piece" << std::endl;
            return false;
        }

        // Simulate the move and check if the king is in check
        char vacant_spot = chess_board[dest_i][dest_j];
        chess_board[start_i][start_j] = '.';
        chess_board[dest_i][dest_j] = piece;

        if (king_in_check(chess_board, (piece == 'Q') ? 'W' : 'B'))
        {
            std::cout << "Move puts King in check, illegal move!" << std::endl;
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
            std::cout << "Invalid knight move!" << std::endl;
            return false;
        }

        // Capture Verification
        if (chess_board[dest_i][dest_j] != '.' &&
            ((piece == 'N' && isupper(chess_board[dest_i][dest_j])) ||
             (piece == 'n' && islower(chess_board[dest_i][dest_j]))))
        {
            std::cout << "Knight cannot capture its own piece!" << std::endl;
            return false;
        }

        // Simulate the move and check if the king is in check
        char vacant_spot = chess_board[dest_i][dest_j];
        chess_board[start_i][start_j] = '.';
        chess_board[dest_i][dest_j] = piece;

        if (king_in_check(chess_board, (piece == 'N') ? 'W' : 'B'))
        {
            std::cout << "Move puts King in check, illegal move!" << std::endl;
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

        // Checking For King Side Castling(Castling Claimed)
        if (row_diff == 0 && col_diff == 2 && dest_j > start_j && !player_king_moved && !king_side_rook_moved)
        {
            std::cout << "Checking For King Side Castling(Castling Claimed)" << std::endl;
            // Checking No piece is between the king and the rook
            for (int j = start_j; j < 7; j++)
            {
                if (chess_board[start_i][j] != '.' && chess_board[start_i][j] != 'K' && chess_board[start_i][j] != 'k') // TODO
                {
                    std::cout << "Can't Castle Piece in between" << std::endl;
                    return false;
                }
                chess_board[start_i][start_j] = '.';
                chess_board[start_i][j] = piece;

                if (king_in_check(chess_board, (piece == 'K') ? 'W' : 'B')) // If the Path has any Checks or not
                {
                    std::cout << "King Can't Castle Through Check" << std::endl;
                    chess_board[start_i][j] = '.';
                    chess_board[start_i][start_j] = piece;
                    return false;
                }
                chess_board[start_i][j] = '.';
                chess_board[start_i][start_j] = piece;
            }
            // Castling Succesful
            std::cout << "KingSide Castling SUccesful" << std::endl;
            chess_board[dest_i][dest_j] = piece;
            chess_board[dest_i][dest_j - 1] = piece == 'K' ? 'R' : 'r';
            chess_board[dest_i][7] = '.';
            chess_board[start_i][start_j] = '.';
            return true;
        }

        // Checking For Queen Side Castling(Castling Claimed)
        if (col_diff == 2 && dest_j < start_j && !player_king_moved && !queen_side_rook_moved)
        {
            std::cout << "Checking For Queen Side Castling(Castling Claimed)" << std::endl;

            for (int j = start_j; j > 1; j--)
            {
                if (chess_board[start_i][j] != '.' && chess_board[start_i][j] != 'K' && chess_board[start_i][j] != 'k') // TODO
                {
                    std::cout << "Can't Castle Piece in between" << std::endl;
                    return false;
                }
                chess_board[start_i][start_j] = '.';
                chess_board[start_i][j] = piece;

                if (king_in_check(chess_board, (piece == 'K') ? 'W' : 'B'))
                {
                    std::cout << "King Can't Castle Through Check" << std::endl;
                    chess_board[start_i][j] = '.';
                    chess_board[start_i][start_j] = piece;
                    return false;
                }
                chess_board[start_i][j] = '.';
                chess_board[start_i][start_j] = piece;
            }
            if (chess_board[start_i][1] != '.') // As Castling Above is only checking for > 1
            {
                std::cout << "Can't Castle Piece in between" << std::endl;
                return false;
            }

            chess_board[dest_i][dest_j] = piece;
            chess_board[dest_i][dest_j + 1] = piece == 'K' ? 'R' : 'r';
            std::cout << "KingSide Castling SUccesful" << std::endl;
            chess_board[dest_i][0] = '.';
            chess_board[start_i][start_j] = '.';
            return true;
        }
        // King can only move one step in any direction
        if (row_diff > 1 || col_diff > 1)
        {
            std::cout << "King can only move one square!" << std::endl;
            return false;
        }

        // Capture Verification
        if (chess_board[dest_i][dest_j] != '.' &&
            ((piece == 'K' && isupper(chess_board[dest_i][dest_j])) ||
             (piece == 'k' && islower(chess_board[dest_i][dest_j]))))
        {
            std::cout << "King cannot capture its own piece!" << std::endl;
            return false;
        }

        // Simulate the move and check if the king is in check
        char vacant_spot = chess_board[dest_i][dest_j];
        chess_board[start_i][start_j] = '.';
        chess_board[dest_i][dest_j] = piece;

        if (king_in_check(chess_board, (piece == 'K') ? 'W' : 'B'))
        {
            std::cout << "Move puts King in check, illegal move!" << std::endl;
            chess_board[start_i][start_j] = piece;
            chess_board[dest_i][dest_j] = vacant_spot;
            return false;
        }

        player_king_moved = true;
        return true; // ✅ Valid move
    }

    std::cout << "something bad occured" << std::endl;
    return false;
}

bool move_is_legal(std::vector<std::vector<char>> &chess_board, const std::string &player_move_start, const std::string player_move_dest, char player_color, const std::string opponent_move_start, const std::string opponent_move_dest, bool &player_king_moved, bool &player_king_side_rook_moved, bool &player_queen_side_rook_moved)
{
    std::cout << "Checking legality: " << player_move_start << " to " << player_move_dest << std::endl;
    // Input to be received in format 6,4 to 4,4 for white or 1,4 to 3,4 for black
    if (player_move_start.size() != 3 || player_move_dest.size() != 3)
    {
        std::cout << "invalid input format length , input should be size 3 in format 6,4  OR  2,4   e.t.c." << std::endl;
        return false;
    }

    if (player_move_start[0] < '0' || player_move_start[0] > '7' || player_move_start[2] < '0' || player_move_start[2] > '7')
    {
        std::cout << "Start Move input out of bounds (must be between 0 and 7)" << std::endl;
        return false;
    }
    if (player_move_dest[0] < '0' || player_move_dest[0] > '7' || player_move_dest[2] < '0' || player_move_dest[2] > '7')
    {
        std::cout << "Destination Move input out of bounds (must be between 0 and 7)" << std::endl;
        return false;
    }

    int start_row = player_move_start[0] - '0'; // Convert character to integer
    int start_col = player_move_start[2] - '0';

    int dest_row = player_move_dest[0] - '0';
    int dest_col = player_move_dest[2] - '0';

    char piece_to_move = chess_board[start_row][start_col];
    if (player_move_start == player_move_dest)
    {
        std::cout << "Starting and Destination cannot be the same" << std::endl;
        return false;
    }
    if (piece_to_move == '.')
    {
        std::cout << "Invalid Move , Select A square with a piece" << std::endl;
        return false;
    }
    if (player_color == 'W' && islower(piece_to_move))
    {
        std::cout << "Invalid Move Select Your own piece" << std::endl;
        return false;
    }
    if (player_color == 'B' && isupper(piece_to_move))
    {
        std::cout << "Invalid Move select your own piece" << std::endl;
        return false;
    }
    std::cout << "Checking Piece Legality and Move" << std::endl;
    if (check_piece_legality_and_move(chess_board, piece_to_move, player_move_start, player_move_dest, opponent_move_start, opponent_move_dest, player_king_moved, player_king_side_rook_moved, player_queen_side_rook_moved))
    {
        std::cout << "THe move is Valid ... Updating Board...." << std::endl;
        return true;
    }
    else
    {
        std::cout << "The move is Illegal.. Try again" << std::endl;
    }
    return false;
}

void start_game(std::vector<std::vector<char>> &chess_board, std::unordered_map<char, std::string> &chess_pieces)
{
    std::string white_move_start, white_move_dest; // Used Primarily for detecting En-Passant and keeping track of move order
    std::string black_move_start, black_move_dest;
    bool white_king_moved = false, black_king_moved = false; // Helps in Determining Castling Rights of the King
    bool white_rook_king_side_moved = false, white_rook_queen_side_moved = false;
    bool black_rook_king_side_moved = false, black_rook_queen_side_moved = false;

    std::vector<std::string> moves_played_UCI; // For keeping individual moves in track in UCI format

    while (true) // Infinite loop until game ends
    {
        // **White's Turn**
        while (true)
        {
            display_board(chess_board, chess_pieces);
            std::cout << "\n♔ White's Turn: Pick the piece you want to move (Format: row,col or 'exit' to quit/Resign): ";
            std::cin >> white_move_start;
            if (white_move_start == "exit")
            {
                std::cout << "WHite Resigned" << std::endl;
                goto end; // Exit condition
            }
            std::cout << "♔ White's Turn: Pick the destination (Format: row,col): ";
            std::cin >> white_move_dest;
            if (white_move_dest == "exit")
            {
                std::cout << "white resigned" << std::endl;
                goto end; // Exit condition
            }
            if (move_is_legal(chess_board, white_move_start, white_move_dest, 'W', black_move_start, black_move_dest, white_king_moved, white_rook_king_side_moved, white_rook_queen_side_moved))
            {
                std::cout << "✅ White's move executed successfully!\n";
                if (!black_move_start.empty())
                    std::cout << "Black's Last Move was " << black_move_start << "TO " << black_move_dest << std::endl;

                moves_played_UCI.push_back(convert_indices_to_UCI(white_move_start, white_move_dest)); // Storing white's Move in Moves Played UCI
                break;                                                                                 // Move was legal, break out of loop
            }
            std::cout << "⚠️  Illegal move! Try again.\n";
        }

        // **Black's Turn**
        while (true)
        {
            display_board(chess_board, chess_pieces);

            std::cout << "\n♚ Black's Turn: Pick the piece you want to move (Format: row,col or 'exit' to quit): ";
            std::cin >> black_move_start;
            if (black_move_start == "exit")
            {
                std::cout << "Black Resigned" << std::endl;
                goto end;
            }
            std::cout << "♚ Black's Turn: Pick the destination (Format: row,col): ";
            std::cin >> black_move_dest;
            if (black_move_dest == "exit")
            {
                std::cout << "Black Resigned !" << std::endl;
                goto end;
            }
            if (move_is_legal(chess_board, black_move_start, black_move_dest, 'B', white_move_start, white_move_dest, black_king_moved, black_rook_king_side_moved, black_rook_queen_side_moved))
            {
                std::cout << "✅ Black's move executed successfully!\n";
                if (!white_move_start.empty())
                    std::cout << "White's Last Move was " << white_move_start << "TO " << white_move_dest << std::endl;

                moves_played_UCI.push_back(convert_indices_to_UCI(black_move_start, black_move_dest)); // Storing black's Move in Moves Played UCI
                break;                                                                                 // Move was legal, break out of loop
            }
            std::cout << "⚠️  Illegal move! Try again.\n";
        }
    }

    end: // Label for ending execution

    std::cout << "Moves Played IN UCI are" << std::endl;

    for (int i = 0; i < moves_played_UCI.size(); i++)
    {
        std::cout << moves_played_UCI[i] << " ";
    }
    std::cout << std::endl;

    // std::cout << "Select Row and Col for the piece to select and generate legal moves for" << std::endl;
    // int row;
    // int col;

    // std::cout << "Enter row\n";
    // std::cin >> row;

    // std::cout << "enter col \n";
    // std::cin >> col;

    // if(chess_board[row][col] == '.')
    // {
    //     std::cout << "select a piece\n";
    //     exit(1);
    // }

    // char color = isupper(chess_board[row][col]) ? 'W' : 'B';
    // std::vector<std::string> moves_generated = generate_legal_moves_for_a_piece(chess_board, color, row, col);
    // std::cout << "Moves Generated are\n";

    // for (int i = 0; i < moves_generated.size(); i++)
    // {
    //     std::cout << moves_generated[i] << std::endl;
    // }




    char player_color__;
    std::cout << "Choose which side to print all legal moves for either 'W' Or 'B' \n";
    std::cin >> player_color__;

    int total_possible_moves = print_all_legal_moves_for_a_position(chess_board, player_color__,chess_pieces);
    std::cout << "The Total Count of Possible Moves in the Position are -> " << total_possible_moves<< std::endl;
    }
