#include "Evaluation.h"
#include <cctype>

const int PAWN_VALUE = 100;
const int KNIGHT_VALUE = 320;
const int BISHOP_VALUE = 330;
const int ROOK_VALUE = 500;
const int QUEEN_VALUE = 900;
const int KING_VALUE = 20000;


// Evaluation For different Pieces in Different Parts ot the game

const int PAWN_PST_MG[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5, 5, 10, 25, 25, 10, 5, 5},
    {0, 0, 0, 20, 20, 0, 0, 0},
    {5, -5, -10, 0, 0, -10, -5, 5},
    {5, 10, 10, -20, -20, 10, 10, 5},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const int PAWN_PST_EG[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {10, 10, 10, 10, 10, 10, 10, 10},
    {5, 5, 5, 5, 5, 5, 5, 5},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {5, 5, 5, 5, 5, 5, 5, 5},
    {10, 10, 10, 10, 10, 10, 10, 10},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const int KNIGHT_PST_MG[8][8] = {
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20, 0, 0, 0, 0, -20, -40},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-30, 5, 15, 20, 20, 15, 5, -30},
    {-30, 0, 15, 20, 20, 15, 0, -30},
    {-30, 5, 10, 15, 15, 10, 5, -30},
    {-40, -20, 0, 5, 5, 0, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}};

const int KNIGHT_PST_EG[8][8] = {
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20, 0, 0, 0, 0, -20, -40},
    {-30, 0, 10, 10, 10, 10, 0, -30},
    {-30, 0, 10, 20, 20, 10, 0, -30},
    {-30, 0, 10, 20, 20, 10, 0, -30},
    {-30, 0, 10, 10, 10, 10, 0, -30},
    {-40, -20, 0, 0, 0, 0, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}};

const int BISHOP_PST_MG[8][8] = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10, 5, 0, 0, 0, 0, 5, -10},
    {-10, 10, 10, 10, 10, 10, 10, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 5, 5, 10, 10, 5, 5, -10},
    {-10, 0, 5, 10, 10, 5, 0, -10},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20}};

const int BISHOP_PST_EG[8][8] = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 10, 10, 10, 10, 10, 10, -10},
    {-10, 10, 10, 10, 10, 10, 10, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20}};

const int ROOK_PST_MG[8][8] = {
    {0, 0, 0, 5, 5, 0, 0, 0},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {5, 10, 10, 10, 10, 10, 10, 5},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const int ROOK_PST_EG[8][8] = {
    {0, 0, 0, 5, 5, 0, 0, 0},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {5, 10, 10, 10, 10, 10, 10, 5},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const int QUEEN_PST_MG[8][8] = {
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    {-5, 0, 5, 5, 5, 5, 0, -5},
    {0, 0, 5, 5, 5, 5, 0, -5},
    {-10, 5, 5, 5, 5, 5, 0, -10},
    {-10, 0, 5, 0, 0, 0, 0, -10},
    {-20, -10, -10, -5, -5, -10, -10, -20}};

const int QUEEN_PST_EG[8][8] = {
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    {-5, 0, 5, 5, 5, 5, 0, -5},
    {0, 0, 5, 5, 5, 5, 0, -5},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-20, -10, -10, -5, -5, -10, -10, -20}};

const int KING_PST_MG[8][8] = {
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-20, -30, -30, -40, -40, -30, -30, -20},
    {-10, -20, -20, -20, -20, -20, -20, -10},
    {20, 20, 0, 0, 0, 0, 20, 20},
    {20, 30, 10, 0, 0, 10, 30, 20}};

const int KING_PST_EG[8][8] = {
    {-50, -40, -30, -20, -20, -30, -40, -50},
    {-30, -20, -10, 0, 0, -10, -20, -30},
    {-30, -10, 20, 30, 30, 20, -10, -30},
    {-30, -10, 30, 40, 40, 30, -10, -30},
    {-30, -10, 30, 40, 40, 30, -10, -30},
    {-30, -10, 20, 30, 30, 20, -10, -30},
    {-30, -30, 0, 0, 0, 0, -30, -30},
    {-50, -30, -30, -30, -30, -30, -30, -50}};

bool is_endgame(std::vector<std::vector<char>> &board)
{
    int white_material = 0;
    int black_material = 0;
    int white_queen = 0, black_queen = 0;
    int white_pawns = 0, black_pawns = 0;

    for (const auto &row : board)
    {
        for (char piece : row)
        {
            switch (piece)
            {
            case 'P':
                white_material += PAWN_VALUE;
                white_pawns++;
                break;
            case 'N':
                white_material += KNIGHT_VALUE;
                break;
            case 'B':
                white_material += BISHOP_VALUE;
                break;
            case 'R':
                white_material += ROOK_VALUE;
                break;
            case 'Q':
                white_material += QUEEN_VALUE;
                white_queen++;
                break;
            case 'p':
                black_material += PAWN_VALUE;
                black_pawns++;
                break;
            case 'n':
                black_material += KNIGHT_VALUE;
                break;
            case 'b':
                black_material += BISHOP_VALUE;
                break;
            case 'r':
                black_material += ROOK_VALUE;
                break;
            case 'q':
                black_material += QUEEN_VALUE;
                black_queen++;
                break;
            }
        }
    }

    int total_material = white_material + black_material;

    // Heuristics for endgame:
    // - No queens or only one queen with low material
    // - Both sides have < certain threshold material (say 20)
    // - Few pawns left
    if ((white_queen + black_queen == 0 && total_material < 2400) ||
        (white_queen + black_queen == 1 && total_material < 1800) ||
        (white_pawns + black_pawns) <= 4)
    {
        return true;
    }

    return false;
}

int static_evaluate(std::vector<std::vector<char>> &board, char ai_color,char current_turn)
{
    int eval = 0;
    bool endgame = is_endgame(board);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            char piece = board[i][j];
            if (piece == '.')
                continue;

            bool is_white = isupper(piece);
            int sign = is_white ? 1 : -1;
            int value = 0;

            // From white's perspective, always flip row for white
            int row = is_white ? i : 7 - i;
            // int row = i;

            switch (tolower(piece))
            {
            case 'p':
                value = PAWN_VALUE + (endgame ? PAWN_PST_EG[row][j] : PAWN_PST_MG[row][j]);
                break;
            case 'n':
                value = KNIGHT_VALUE + KNIGHT_PST_MG[row][j];
                break;
            case 'b':
                value = BISHOP_VALUE + BISHOP_PST_MG[row][j];
                break;
            case 'r':
                value = ROOK_VALUE + ROOK_PST_MG[row][j];
                break;
            case 'q':
                value = QUEEN_VALUE + QUEEN_PST_MG[row][j];
                break;
            case 'k':
                value = KING_VALUE + (endgame ? KING_PST_EG[row][j] : KING_PST_MG[row][j]);
                break;
            }

            eval += (sign * value);
        }
    }

    // Return evaluation from the POV of the current player
    return (ai_color == 'W') ? eval : -eval;
    // return eval;
}
