/**
 * @file piece.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstdint>
typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard
//   0b0000 .... 0000
//     ^            ^
// idx 0        idx 63

class Piece {

private:
    // 1 = tile has piece / 0 = tile does not have piece
    static const char pieceMask = 0b01;
    // 1 = white / 0 = black
    static const char colorMask = 0b10;

public:
    static const int isEmpty = 0;
    static const int isPiece = 1;
    static const int black = 0;
    static const int white = 1;
    static const int bitboardSize = 64;

    static const int blackPiece = 0b01;
    static const int whitePiece = 0b11;

    /**
     * @brief Returns the color bit
     */
    static int color(int piece);
    /**
     * @brief Returns the piece bit
     */
    static bool piece(int piece);
    /**
     * @brief Returns the bit at a given index from a bitboard
     */
    static bool at(bitboard bb, int idx);
};