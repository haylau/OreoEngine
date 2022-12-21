/**
 * @file movegen.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/movegen.h"

static int inline dist(int from, int to) {
    return MoveData::dist(from, to);
} 
static bool inline at(bitboard bb, int idx) {
    return Piece::at(bb, idx);
}

MoveGen::MoveGen(bitboard bb_piece, bitboard bb_color) {
    this->bb_piece = bb_piece;
    this->bb_color = bb_color;
    this->bb_moves = 0;
    genMoves();
}

bitboard MoveGen::getMoves() {
    return this->bb_moves;
}

bool MoveGen::isAdjacent(int idx, int color) {
    for(int dir : MoveData::moveOffsets) {
        int target = idx + dir;
        if(target < 0 || target > 64) continue;
        // if a
        if(at(bb_piece, target) && at(bb_color, color)) return true;
    }
    return false;
}