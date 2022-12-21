/**
 * @file board.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/piece.h"
#include <cstdint>
#include <vector>
#include <stdexcept>


typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard

class Board {

private:
    bitboard bb_piece;
    bitboard bb_color;

public:
    Board();
    Board(std::vector<int> pieces);
};