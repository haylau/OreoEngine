/**
 * @file movegen.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
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
static bool inline at(bitboard bb, int idx, int value) {
    return Piece::at(bb, idx, value);
}
static void inline addMove(bitboard& bb, int idx, int value) {
    return Piece::set(bb, idx, value);
}

/**
 * Class functionality
 */

MoveGen::MoveGen(bitboard bb_piece, bitboard bb_color, int colorToMove)
    : bb_piece(bb_piece), bb_color(bb_color), bb_moves(0), colorToMove(colorToMove) {
    if(colorToMove != 0 && colorToMove != 1) throw std::invalid_argument("Color must be 0 or 1");
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
        if(at(bb_piece, target, 1) && at(bb_color, target, color)) return true;
    }
    return false;
}

void MoveGen::genMoves() {
    // valid move must find opponent then empty space in the same direction
    for(int idx = 0; idx < Board::boardSize; ++idx) {
        // piece here; cant play
        if(at(bb_piece, idx, 1)) continue;
        for(int dir = 0; dir < (int)MoveData::moveOffsets.size(); ++dir) {
            int offset = MoveData::moveOffsets[dir];
            // check if idx already has move set
            if(at(bb_moves, idx, 1)) break;
            bool foundOpponent = false;
            for(int dist = 1; dist < MoveData::distToEdge[idx][dir]; ++dist) {
                int target = idx + (dist * offset);
                // no piece in this direction
                if(at(bb_piece, target, 0)) break;
                // found opponent piece
                if(!foundOpponent && at(bb_color, target, this->opponentColor)) {
                    foundOpponent = true;
                    continue;
                }
                // found player piece; cant play in this direction
                if(at(bb_color, target, this->colorToMove)) {
                    // if encapsulating opponent, add move
                    if(foundOpponent) {
                        addMove(bb_moves, idx, 1);
                    }
                    // otherwise cant play here
                    break;
                }
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const MoveGen& mg) {
    bitboard moves = mg.getMoves();
    for(int idx = 0; idx < Board::boardSize; ++idx) {
        if((moves & (1ULL << idx)) != 0ULL) {
            os << Board::indexToMove(idx) << " ";
        }
    }
    return os;
}