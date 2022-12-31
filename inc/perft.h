/**
 * @file perft.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief Perft testing for move generation
 * @version 0.1
 * @date 2022-12-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>

#include "../inc/board.h"

class Perft {

private:
    static std::unordered_map<bitboard, bitboard> tt_white;
    static std::unordered_map<bitboard, bitboard> tt_black;
    static long count(const Board& b, int depth);
public:
    static void runPerft(const Board& b, int depth, const std::vector<long>& correctVals = {});

};
