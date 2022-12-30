/**
 * @file main.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/board.h"

#include <iostream>

int main() {

    std::vector<int> debug;
    debug.insert(debug.end(), 1, Piece::whitePiece);
    debug.insert(debug.end(), 63, Piece::empty);

    Board debugBoard(debug);
    std::cout << debugBoard << std::endl;

    Board b;
    std::cout << b << std::endl;
    std::string input;
    do {
        std::cin >> input;
        input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
        b.makeMove(input);
        std::cout << b << std::endl;
    } while(input != "exit");
    // MoveGen mg(b.getWhiteBoard(), b.getBlackBoard(), b.getColorToMove());
    // std::cout << mg << std::endl;
    return 0;
}