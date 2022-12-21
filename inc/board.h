/**
 * @file board.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/piece.h"
#include <cstdint>
#include <map>
#include <stdexcept>
#include <vector>
#include <regex>

typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard

class Board {

private:
    const std::map<char, int> files = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};

    bitboard bb_piece;
    bitboard bb_color;

    /**
     * @brief Initalizes a Board object with the starting position
     */
    void initBoard();
    /**
     * @brief Initalizes a Board object with a specific position stored in pieces
     * @param pieces vector of pieces on the board
     */
    void initBoard(std::vector<int> pieces);

public:
    /**
     * @brief Construct a new Board object
     */
    Board();
    /**
     * @brief Construct a new Board object from a vector of pieces
     * @param pieces vector of pieces on the board
     * @pre 'pieces' Must contain 64 pieces to initalize
     */
    Board(std::vector<int> pieces);

    int moveToIndex(std::string move);
    std::string indexToMove(int index);
};