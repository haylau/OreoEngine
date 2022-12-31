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

#pragma once

#include "../inc/movedata.h"

#include <cstdint>
#include <map>
#include <regex>
#include <stdexcept>
#include <vector>

typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard
//   0b0000 .... 0000
//     ^            ^
// idx 63       idx 0

class Piece {

private:
    // 1 = tile has piece / 0 = tile does not have piece
    static const char pieceMask = 0b01;
    // 1 = white / 0 = black
    static const char colorMask = 0b10;

public:
    static const int empty = 0;
    static const int occupied = 1;
    static const int black = 0;
    static const int white = 1;
    static const int bitboardSize = 64;
    static const int blackPiece = 0b01;
    static const int whitePiece = 0b11;

    static const std::map<char, int> fileToInt;
    static const std::map<int, char> intToFile;
    static const std::map<char, int> rankToInt;
    static const std::map<int, char> intToRank;

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
    static bool at(bitboard bb, int idx, int value);
    /**
     * @brief Modifies the bitboard
     * @param bb
     * @param idx
     * @param value
     */
    static void set(bitboard& bb, int idx, int value);
    static int size(bitboard bb);
    static int makeMove(bitboard& bb_white, bitboard& bb_black, int& colorToMove, int index);

    static std::vector<int> toVector(bitboard bb);
    //    [0] .... [0]
    //     ^       ^
    // idx 0       idx 63
    static int moveToIndex(std::string move);
    static std::string indexToMove(int index);
};