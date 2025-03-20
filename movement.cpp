#include "movement.h"
#include "chessboard.h"
#include "king_check.h"
#include <iostream>
#include <vector>
#include<string>
#include <unordered_map>
#include <cctype>

bool check_piece_legality_and_move(std::vector<std::vector<char>> &chess_board, char piece, const std::string &move_start, const std::string move_dest)
{
    int start_i = move_start[0] - '0';
    int start_j = move_start[2] - '0';
    int dest_i = move_dest[0] - '0';
    int dest_j = move_dest[2] - '0';

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
                // Verifying Capture
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

                return true;
            }
            else
            {
                std::cout << "Fristd::endly Peace is on Destination" << std::endl;
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
                return true;
            }
            else
            {
                std::cout << "Fristd::endly Peace is on Destination" << std::endl;
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

        return true; // ✅ Valid move
    }

    std::cout << "something bad occured" << std::endl;
    return false;
}

bool move_is_legal(std::vector<std::vector<char>> &chess_board, const std::string &move_start, const std::string move_dest, char player_color)
{
    std::cout << "Checking legality: " << move_start << " to " << move_dest << std::endl;
    // Input to be received in format 6,4 to 4,4 for white or 1,4 to 3,4 for black
    if (move_start.size() != 3 || move_dest.size() != 3)
    {
        std::cout << "invalid input format length , input should be size 3 in format 6,4  OR  2,4   e.t.c." << std::endl;
        return false;
    }

    if (move_start[0] < '0' || move_start[0] > '7' || move_start[2] < '0' || move_start[2] > '7')
    {
        std::cout << "Start Move input out of bounds (must be between 0 and 7)" << std::endl;
        return false;
    }
    if (move_dest[0] < '0' || move_dest[0] > '7' || move_dest[2] < '0' || move_dest[2] > '7')
    {
        std::cout << "Destination Move input out of bounds (must be between 0 and 7)" << std::endl;
        return false;
    }

    int start_row = move_start[0] - '0'; // Convert character to integer
    int start_col = move_start[2] - '0';

    int dest_row = move_dest[0] - '0';
    int dest_col = move_dest[2] - '0';

    char piece_to_move = chess_board[start_row][start_col];
    if (move_start == move_dest)
    {
        std::cout << "Starting and Destination cannot be the same" << std::endl; // TO-DO
        return false;
    }
    if (piece_to_move == '.')
    {
        std::cout << "Invalid Move , Select A square with a piece" << std::endl; // Handling Errors TO-DO
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
    if (check_piece_legality_and_move(chess_board, piece_to_move, move_start, move_dest))
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
    while (true) // Infinite loop until game ends
    {
        std::string move_start, move_dest;

        // **White's Turn**
        while (true)
        {
            display_board(chess_board,chess_pieces);
            std::cout << "\n♔ White's Turn: Pick the piece you want to move (Format: row,col or 'exit' to quit/Resign): ";
            std::cin >> move_start;
            if (move_start == "exit")
            {
                std::cout << "WHite Resigned" << std::endl;
                exit(1); // Exit condition
            }
            std::cout << "♔ White's Turn: Pick the destination (Format: row,col): ";
            std::cin >> move_dest;
            if (move_dest == "exit")
            {
                std::cout << "white resigned" << std::endl;
                exit(1); // Exit condition
            }
            if (move_is_legal(chess_board, move_start, move_dest, 'W'))
            {
                std::cout << "✅ White's move executed successfully!\n";
                break; // Move was legal, break out of loop
            }
            std::cout << "⚠️  Illegal move! Try again.\n";
        }

        // **Black's Turn**
        while (true)
        {
            display_board(chess_board,chess_pieces);

            std::cout << "\n♚ Black's Turn: Pick the piece you want to move (Format: row,col or 'exit' to quit): ";
            std::cin >> move_start;
            if (move_start == "exit")
            {
                std::cout << "Black Resigned" << std::endl;
                exit(1);
            }
            std::cout << "♚ Black's Turn: Pick the destination (Format: row,col): ";
            std::cin >> move_dest;
            if (move_dest == "exit")
            {
                std::cout << "Black Resigned !" << std::endl;
                exit(1);
            }
            if (move_is_legal(chess_board, move_start, move_dest, 'B'))
            {
                std::cout << "✅ Black's move executed successfully!\n";
                break; // Move was legal, break out of loop
            }
            std::cout << "⚠️  Illegal move! Try again.\n";
        }
    }

}

