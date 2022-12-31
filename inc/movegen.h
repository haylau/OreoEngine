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
    /**
     * @brief Construct a new Move Gen object and calculate moves
     * 
     * @param bb_white 
     * @param bb_black 
     * @param colorToMove 
     */
    MoveGen(bitboard bb_white, bitboard bb_black, int colorToMove);
    /**
     * @brief Construct a new Move Gen object without calculating moves
     * 
     * @param bb_white 
     * @param bb_black 
     * @param bb_moves 
     * @param colorToMove 
     */
    MoveGen(bitboard bb_white, bitboard bb_black, bitboard bb_moves, int colorToMove);
    bitboard getMoves() const;
    friend std::ostream& operator<<(std::ostream& os, const MoveGen& mg);
};