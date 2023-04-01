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

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include "../inc/board.h"
#include "../inc/piece.h"
#include "../inc/movegen.h"
#include "../inc/engine.h"

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

    // std::string input = "";
    // std::string turn = color == Piece::white ? "White" : "Black";
    // std::cout << "You are playing as " << turn << std::endl;
    // bool playerTurn = color == Piece::white ? true : false;
    // while(input != "exit" || b.isComplete()) {
    //     while(playerTurn) {
    //         std::cout << b << std::endl;
    //         std::cin >> input;
    //         playerTurn = b.makeMove(input);
    //     }
    //     std::cout << b << std::endl;
    //     std::string oppMove = Board::indexToMove(e.getBestMove(7, b));
    //     std::cout << "Ill play " << oppMove << std::endl;
    //     if(!playerTurn) playerTurn = true;
    //     b.makeMove(oppMove);
    // }

    // b.makeMove("d6");
    // b.makeMove("c4");
    // std::cout << b << std::endl;
    // std::cout << "best move is: " << Board::indexToMove(e.getBestMove(7, b)) << std::endl;

    return 0;
}