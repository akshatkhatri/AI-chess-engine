#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <unordered_map>
#include <string>

void print_welcome_message();
void display_board(std::vector<std::vector<char>> &chess_board,std::unordered_map<char, std::string>&chess_pieces);


#endif