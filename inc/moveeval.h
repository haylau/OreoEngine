/**
 * @file moveeval.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../inc/board.h"

class MoveEval {

private:

    MoveEval(); // cannot be initalized

    static int getPosVal(const Board& b);
    static int getMoveCountVal(const Board& b);

public:

    static const int whiteVictory = 10000;
    static const int blackVictory = -10000;

    static const int posVal[64];
    static const int moveCountVal = 10;
    static int getEval(const Board& b);

};
