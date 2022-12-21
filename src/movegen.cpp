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

/**
 *  Inline functions
 */
static int inline dist(int from, int to) {
    return MoveData::dist(from, to);
}
static bool inline at(bitboard bb, int idx) {
    return Piece::at(bb, idx);
}
static void inline addMove(bitboard& bb, int idx, int value) {
    return Piece::set(bb, idx, value);
}

/**
 * Class functionality
 */

MoveGen::MoveGen(bitboard bb_piece, bitboard bb_color, int colorToMove)
    : bb_piece(bb_piece), bb_color(bb_color), bb_moves(0), colorToMove(colorToMove) {
    if(colorToMove != 0 || colorToMove != 1) throw std::invalid_argument("Color must be 0 or 1");
    this->opponentColor = this->colorToMove == Piece::white ? Piece::black : Piece::white;
    genMoves();
}

bitboard MoveGen::getMoves() const {
    return this->bb_moves;
}

bool MoveGen::isAdjacent(int idx, int color) {
    for(int dir : MoveData::moveOffsets) {
        int target = idx + dir;
        if(target < 0 || target > 64) continue;
        // if a piece of 'color' is adjacent to idx
        if(at(bb_piece, target) && at(bb_color, color)) return true;
    }
    return false;
}

void MoveGen::genMoves() {
    for(int idx = 0; idx < Board::boardSize; ++idx) {
        if(!isAdjacent(idx, this->colorToMove)) continue; // move would be illegal
        for(int dir : MoveData::moveOffsets) {
            // check if idx already has move set
            if(at(bb_moves, idx)) break;
            for(int dist = 0; dist < MoveData::distToEdge[idx][dir]; ++dist) {
                int target = idx + (dist * dir);
                // if move encapsulates, set move
                if(at(bb_color, opponentColor) && at(bb_piece, target)) {
                    addMove(bb_moves, idx, 1);
                    break;
                }
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const MoveGen& mg) {
    bitboard moves = mg.getMoves();
    for(int idx = 0; idx < Board::boardSize; ++idx) {
        if(at(mg.getMoves(), idx)) {
            os << Board::indexToMove(idx) << " ";
        }
    }
    return os;
}