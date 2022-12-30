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
static bool inline at(bitboard bb, int idx, int value) {
    return Piece::at(bb, idx, value);
}
static void inline add(bitboard& bb, int idx, int value) {
    return Piece::set(bb, idx, value);
}

/**
 * Class functionality
 */

MoveGen::MoveGen(bitboard bb_white, bitboard bb_black, int colorToMove)
    : bb_white(bb_white), bb_black(bb_black), bb_moves(0), colorToMove(colorToMove) {
    if(colorToMove != 0 && colorToMove != 1) throw std::invalid_argument("Color must be 0 or 1");
    this->bb_piece = this->bb_white | this->bb_black;
    this->opponentColor = this->colorToMove == Piece::white ? Piece::black : Piece::white;
    genMoves();
}

MoveGen::MoveGen(){};

bitboard MoveGen::getMoves() const {
    return this->bb_moves;
}

// bool MoveGen::isAdjacent(int idx, int color) {
//     for(int dir : MoveData::moveOffsets) {
//         int target = idx + dir;
//         if(target < 0 || target > 64) continue;
//         // if a piece of 'color' is adjacent to idx
//         if(at(bb_piece, target, 1) && at(bb_color, target, color)) return true;
//     }
//     return false;
// }

void MoveGen::genMoves() {
    bitboard* playerBoard = Piece::white == this->colorToMove ? &this->bb_white : &this->bb_black;
    bitboard* opponentBoard = Piece::white == this->colorToMove ? &this->bb_black : &this->bb_white;
    // valid move must find opponent then empty space in the same direction
    for(int idx = 0; idx < Piece::bitboardSize; ++idx) {
        // piece here; cant play
        if(at(bb_piece, idx, Piece::occupied)) continue;
        for(int dir = 0; dir < (int)MoveData::moveOffsets.size(); ++dir) {
            int offset = MoveData::moveOffsets[dir];
            // check if idx already has move set
            if(at(bb_moves, idx, 1)) break;
            bool foundOpponent = false;
            for(int dist = 1; dist < MoveData::distToEdge[idx][dir]; ++dist) {
                int target = idx + (dist * offset);
                // no piece in this direction
                if(at(bb_piece, target, Piece::empty)) break;
                // found first opponent piece
                if(!foundOpponent && at(*opponentBoard, target, Piece::occupied)) {
                    foundOpponent = true; // skip other opponent pieces
                    continue;
                }
                // found player piece
                if(at(*playerBoard, target, Piece::occupied)) {
                    // if encapsulating opponent, add move
                    if(foundOpponent) add(bb_moves, idx, Piece::occupied);
                    // otherwise cant play here
                    break;
                }
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const MoveGen& mg) {
    bitboard moves = mg.getMoves();
    for(int idx = 0; idx < Piece::bitboardSize; ++idx) {
        if(at(moves, idx, 1)) {
            auto str = Piece::indexToMove(idx);
            os << str << " ";
        }
    }
    return os;
}