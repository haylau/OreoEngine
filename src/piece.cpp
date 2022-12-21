/**
 * @file piece.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/piece.h"

int Piece::color(int piece) {
    return piece & Piece::colorMask;
}

bool Piece::piece(int piece) {
    return piece & Piece::pieceMask;
}

bool Piece::at(bitboard bb, int idx) {
    return (bb >> (bitboardSize - idx)) & 1;
}