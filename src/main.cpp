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

#include "../inc/board.h"
#include "../inc/engine.h"
#include "../inc/movegen.h"
#include "../inc/piece.h"

#include <chrono>
#include <iostream>
#include <random>
#include <thread>

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    int color = dis(gen) == 1 ? Piece::white : Piece::black;
    std::cout << "I am playing as " << (color == Piece::white ? "White" : "Black") << std::endl;

    Board b;
    Engine e;

    while (!b.isComplete()) {
        std::cout << b << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::string oppMove = Board::indexToMove(e.getBestMove(7, b));
        std::cout << "Ill play " << oppMove << std::endl;
        if (!b.makeMove(oppMove)) {
            // game is over
            int winner = b.getWinner();
            switch (winner) {
            case Piece::white:
                std::cout << "White wins!" << std::endl;
                break;
            case Piece::black:
                std::cout << "Black wins!" << std::endl;
                break;
            case Board::draw:
                std::cout << "Draw!" << std::endl;
                break;
            }
            break;
        }
    }

    return 0;
}