/**
 * @file perft.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief Perft testing for move generation
 * @version 0.1
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/perft.h"

// init static variables (they're empty lol)
std::unordered_map<bitboard, bitboard> Perft::tt_white = [] {
    std::unordered_map<bitboard, bitboard> tt_white = {};
    return tt_white;
}();
std::unordered_map<bitboard, bitboard> Perft::tt_black = [] {
    std::unordered_map<bitboard, bitboard> tt_black = {};
    return tt_black;
}();

void Perft::runPerft(const Board& b, int depth, const std::vector<long>& correctVals) {

    std::cout << "Running Perft.\n\n";

    tt_white.clear();
    tt_black.clear();

    bool correct = (int)correctVals.size() >= depth;
    auto start = std::chrono::high_resolution_clock::now();
    long totalNodes = 0l;

    for(int cur = 1; cur <= depth; ++cur) {
        long numMoves = count(b, cur);
        totalNodes += numMoves;
        std::cout << cur << ": " << std::setw((10) - std::floor(std::log10(cur))) << numMoves;

        if(correct) {
            if(correctVals[cur - 1] != numMoves) {
                std::cout << " ☒ " << correctVals[cur - 1];

            } else {
                std::cout << " ☑";
            }
        }
        std::cout << '\n';
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // convert from n/ms to Mn/s
    double mnps = ((double)totalNodes / ((double)time / 1000.0)) / (1000000.0);

    std::cout << std::setprecision(2) << mnps << " Mnps." << std::endl;
}

long Perft::count(const Board& b, int depth) {
    auto* cur_tt = b.getColorToMove() == Piece::white ? &tt_white : &tt_black;
    bitboard bb_moves = b.getMoves();
    // base case
    if(depth == 1) {
        return Piece::size(bb_moves);
    }
    // recursive case
    int idx = 0, numMoves = 0;
    while(bb_moves) {

        // idx is set
        if(bb_moves & 1) {
            // make move
            bitboard bb_white_next = b.getWhiteBoard(); 
            bitboard bb_black_next = b.getBlackBoard();
            bitboard bb_moves_next = 0;
            int color_next = b.getColorToMove(); 
            Piece::makeMove(bb_white_next, bb_black_next, color_next, idx);
            // check for precalced moves
            bitboard* bb_color_next = color_next == Piece::white ? &bb_white_next : &bb_black_next;
            if(cur_tt->find(*bb_color_next) != cur_tt->end()) {
                // moves exist in table
                bb_moves_next = cur_tt->at(*bb_color_next);
                Board nextPos(bb_white_next, bb_black_next, bb_moves_next, color_next);
                numMoves += count(nextPos, depth - 1);
            }
            else {
                // calc new legal moves 
                Board nextPos(bb_white_next, bb_black_next, color_next);
                cur_tt->insert(std::make_pair(*bb_color_next, nextPos.getMoves()));
                numMoves += count(nextPos, depth - 1);
            }
        }

        // next move
        ++idx;
        bb_moves >>= 1;
    }
    return numMoves;
}