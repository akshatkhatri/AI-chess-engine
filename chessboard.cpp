#include "chessboard.h"
#include<iostream>
#include<vector>
#include<unordered_map>
void print_welcome_message()
{
    std::cout << "=========================================\n";
    std::cout << "       Welcome to Player vs Player Chess \n";
    std::cout << "=========================================\n\n";
    std::cout << ">> Enter your moves in the format: row,col (e.g., 6,4)\n";
    std::cout << ">> Rows and columns are indexed from 0 to 7\n";
    std::cout << ">> First, pick the piece you want to move.\n";
    std::cout << ">> Then, enter the destination where you want to move it.\n";
    std::cout << ">> If the move is legal, we will execute it.\n";
    std::cout << ">> Type 'exit' to quit the game\n";
    std::cout << ">> Have fun and play fair!\n";
    std::cout << "-----------------------------------------\n";
}

void display_board(std::vector<std::vector<char>> &chess_board,std::unordered_map<char, std::string>&chess_pieces)
{
    std::cout << "\n        0         1         2         3         4         5         6         7  \n";
    std::cout << "    -----------------------------------------------------------------------------------\n";
    for (int i = 0; i < 8; i++)
    {
        std::cout << 8 - i << " U  |"; // Row label according to UCN
        for (int j = 0; j < 8; j++)
        {
            if(chess_board[i][j]!='.')
                std::cout << "    " << chess_pieces[chess_board[i][j]] << "    |"; // Extra spaces for width
            else
                std::cout<< "    "<<chess_board[i][j]<< "    |";
        }
        std::cout << "  " << i; // Right-side row label For movement
        std::cout << "\n    -----------------------------------------------------------------------------------\n";
    }
    std::cout << "          A         B         C         D         E         F         G         H  \n"; // Column Labels according to UCN
}

