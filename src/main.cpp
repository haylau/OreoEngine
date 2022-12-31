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
#include "../inc/perft.h"

#include <iostream>

int main() {

// test perft
#if 0
    Board startPos;
    std::vector<long> startPosVals = {4, 12, 56, 244, 1396, 8200, 55092, 390216, 3005288, 24571284, 212258800, 1939886636, 18429641748, 184042084512};
    Perft::runPerft(startPos, 10, startPosVals);
#endif

// test load position
#if 0
    std::vector<int> debug;
    debug.insert(debug.end(), 1, 3);
    debug.insert(debug.end(), 1, 1);
    debug.insert(debug.end(), 6, 0);
    debug.insert(debug.end(), 1, 1);
    debug.insert(debug.end(), 1, 1);
    debug.insert(debug.end(), 54, 0);

    Board debugBoard(debug);
    std::cout << debugBoard << std::endl;
#endif

// test run input
#if 1
    Board b;
    std::cout << b << std::endl;
    std::string input;
    do {
        std::cin >> input;
        input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
        Board copy = b;
        int result = b.makeMove(input);
        // #TODO gameover/skip turn
        std::cout << b << std::endl;
    } while(input != "exit");
    return 0;
#endif
}