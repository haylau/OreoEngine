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

#pragma once

#include "../inc/movedata.h"
#include "../inc/piece.h"

#include <cstdint>
#include <iostream>

typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard

class MoveGen {

private:
    bitboard bb_piece;
    bitboard bb_white;
    bitboard bb_black;
    bitboard bb_moves;

    int colorToMove;
    int opponentColor;
    // bool isAdjacent(int idx, int color);
    void genMoves();

public:
    MoveGen();
    MoveGen(bitboard bb_white, bitboard bb_black, int colorToMove);
    bitboard getMoves() const;
    friend std::ostream& operator<<(std::ostream& os, const MoveGen& mg);
};