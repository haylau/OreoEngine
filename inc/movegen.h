/**
 * @file movegen.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/movedata.h"
#include "../inc/piece.h"
#include <cstdint>

typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard

class MoveGen {

private:
    bitboard bb_piece;
    bitboard bb_color;
    bitboard bb_moves;

    bool isAdjacent(int idx, int color);
    void genMoves();

public:
    MoveGen(bitboard bb_piece, bitboard bb_color);
    bitboard getMoves();
};