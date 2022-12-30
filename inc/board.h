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

#pragma once

#include "../inc/movedata.h"
#include "../inc/movegen.h"
#include "../inc/piece.h"

#include <cstdint>
#include <map>
#include <stdexcept>
#include <vector>

typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard

class Board {

private:
    // linker got angry
    const int blackPiece = 0b01;
    const int whitePiece = 0b11;

    bitboard bb_white;
    bitboard bb_black;

    int colorToMove;

    MoveGen mg;

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
    static const int boardSize = 64;

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

    bitboard getWhiteBoard() const;
    bitboard getBlackBoard() const;
    int getColorToMove() const;

    /**
     * @brief Makes a move on the board
     * This will modify bitboards
     * @pre Move must legal
     * @throw std::runtime_error if Move was illegal
     * @param index Move to make
     */
    int makeMove(int index);
    int makeMove(std::string move);

    friend std::ostream& operator<<(std::ostream& os, const Board& b);
};
