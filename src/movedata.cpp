/**
 * @file movedata.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/movedata.h"

const std::array<int, 8> MoveData::moveOffsets = [] {
    /* Clockwise from Up
     *   -9 -8 -7  7 0 1
     *   -1 () +1  6 - 2
     *   +7 +8 +9  5 4 3
     */
    std::array<int, 8> moveOffsets = {-8, -7, 1, 9, 8, 7, -1, -9};
    return moveOffsets;
}();

const std::array<std::array<int, 8>, 64> MoveData::distToEdge = [] {
    /*
     * a1 b1 c1 d1 e1 f1 g1 h1 | 00 01 02 03 04 05 06 07
     * a2 b2 c2 d2 e2 f2 g2 h2 | 08 09 10 11 12 13 14 15
     * a3 b3 c3 d3 e3 f3 g3 h3 | 16 17 18 19 20 21 22 23
     * a4 b4 c4 d4 e4 f4 g4 h4 | 24 25 26 27 28 29 30 31
     * ------------------------|------------------------
     * a5 b5 c5 d5 e5 f5 g5 h5 | 32 33 34 35 36 37 38 39
     * a6 b6 c6 d6 e6 f6 g6 h6 | 40 41 42 43 44 45 46 47
     * a7 b7 c7 d7 e7 f7 g7 h7 | 48 49 50 51 52 53 54 55
     * a8 b8 c8 d8 e8 f8 g8 h8 | 56 57 58 59 60 61 62 63
     */

    std::array<std::array<int, 8>, 64> dist;
    for(int file = 0; file < 8; ++file) {
        for(int rank = 0; rank < 8; ++rank) {

            int up = rank;
            int right = 7 - file;
            int down = 7 - rank;
            int left = file;

            int idx = rank * 8 + file;

            dist[idx][0] = up;
            dist[idx][1] = std::min(up, right);
            dist[idx][2] = right;
            dist[idx][3] = std::min(right, down);
            dist[idx][4] = down;
            dist[idx][5] = std::min(down, left);
            dist[idx][6] = left;
            dist[idx][7] = std::min(left, up);
        }
    }
    return dist;
}();

int MoveData::dist(int from, int to) {
    if(from < 0 || from > 64 || to < 0 || to > 64) throw std::out_of_range("Invalid Index");
    return distToEdge[from][to];
}