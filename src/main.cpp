/**
 * @file engine.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include "../inc/board.h"
#include "../inc/movegen.h"


int main () {
    Board b;
    MoveGen mg(b.getPieceBoard(), b.getColorBoard(), Piece::white);
    std::cout << mg << std::endl;
    return 0;
}