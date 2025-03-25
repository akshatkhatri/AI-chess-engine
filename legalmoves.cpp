#include "legalmoves.h"
#include<iostream>
#include<string>
#include<vector>
// TO-DO

unsigned long long int count_legal_moves(int depth, std::vector<std::vector<char>> &chess_board,char player_turn, int i, int moves)
{
    if(i > depth) // Base Case
    {
        return moves;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(!chess_board[i][j] == '.' && player_turn == 'W' ? isupper(chess_board[i][j]) : islower(chess_board[i][j]))
            {
                char piece = chess_board[i][j];
                if(piece == 'P' || piece == 'p')
                {
                    if(piece == 'P' && i == 6) // Pawn moving from starting Square
                    {
                        for (int k = i - 1; k <= i - 2; k--)
                        {
                            
                        }
                    }
                    else if (piece == 'P')
                    {
                        //TO-DO
                    }

                    else if(piece == 'p' && i == 1)
                    {
                        for (int k = i + 1; k <= i + 2; k++)
                        {
                            //TODO
                        }
                    }
                    else
                    {
                        //TO DO
                    }
                }
            }
        }
    }
}