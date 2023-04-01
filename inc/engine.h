/**
 * @file engine.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../inc/moveeval.h"
#include "../inc/board.h"

#include <unordered_map>
#include <functional>

class Engine {


private:

    std::unordered_map<std::size_t, int> transpositionTable;
    int numNodes;
    int halfMoves;
    int bestMove;
    Board originalBoard;

    int NegaMax(const Board& board, int depth, int alpha, int beta);
    std::size_t zhash(const Board& board, bitboard moves, int eval);

public:

    Engine();

    int getBestMove(int depth, const Board& board);

};