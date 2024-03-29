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
#include <regex>
#include <stdexcept>
#include <vector>

typedef uint64_t bitboard; // 64-bit integer to be used as a bitboard

class Board {

private:
    // linker got angry
    const int blackPiece = 0b01;
    const int whitePiece = 0b11;

    static const std::map<char, int> fileToInt;
    static const std::map<int, char> intToFile;

    bitboard bb_piece;
    bitboard bb_color;

    int colorToMove;

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
    static const bitboard finishedGame = ~0ULL;
    static const int draw = 2;

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
    Board(const Board& b);

    bool makeMove(std::string);
    bool makeMove(int);

    bitboard getPieceBoard() const;
    bitboard getColorBoard() const;
    int getColorToMove() const;
    bool isComplete() const;
    int getWinner() const;

    void setColorToMove(int color);

    static int moveToIndex(std::string move);
    static std::string indexToMove(int index);

    friend std::ostream& operator<<(std::ostream& os, const Board& b);
};