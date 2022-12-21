#include "../inc/piece.h"

int Piece::color(int piece) {
    return piece & Piece::colorMask;
}

bool Piece::piece(int piece) {
    return piece & Piece::pieceMask;
}