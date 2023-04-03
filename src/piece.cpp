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

int Piece::color(int piece) { return (piece & Piece::colorMask) >> 1; }

bool Piece::piece(int piece) { return piece & Piece::pieceMask; }

bool Piece::at(bitboard bb, int idx, int value) { return ((bb >> (bitboardSize - idx - 1)) & 1) == (bitboard)value; }

void Piece::set(bitboard& bb, int idx, int value) {
    if (value != 0 && value != 1) throw std::invalid_argument("Value must be 0 or 1");
    if (idx < 0 || idx > 64) throw std::invalid_argument("Index must be between [0, 63]");
    bb |= ((bitboard)0b1 << (bitboardSize - idx - 1));
}
