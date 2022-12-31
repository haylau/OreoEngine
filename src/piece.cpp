/**
 * @file piece.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/piece.h"

// init static const variables
const std::map<char, int> Piece::fileToInt = [] {
    std::map<char, int> files = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
    return files;
}();
const std::map<int, char> Piece::intToFile = [] {
    std::map<int, char> files = {{0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'}};
    return files;
}();
const std::map<char, int> Piece::rankToInt = [] {
    std::map<char, int> ranks = {{'1', 7}, {'2', 6}, {'3', 5}, {'4', 4}, {'5', 3}, {'6', 2}, {'7', 1}, {'8', 0}};
    return ranks;
}();
const std::map<int, char> Piece::intToRank = [] {
    std::map<int, char> ranks = {{0, '8'}, {1, '7'}, {2, '6'}, {3, '5'}, {4, '4'}, {5, '3'}, {6, '2'}, {7, '1'}};
    return ranks;
}();

int Piece::color(int piece) {
    return (piece & Piece::colorMask) >> 1;
}

bool Piece::piece(int piece) {
    return piece & Piece::pieceMask;
}

bool Piece::at(bitboard bb, int idx, int value) {
    return ((bb >> idx) & 1) == (bitboard)value;
}

void Piece::set(bitboard& bb, int idx, int value) {
    if(value != 0 && value != 1) throw std::invalid_argument("Value must be 0 or 1");
    if(idx < 0 || idx > 64) throw std::invalid_argument("Index must be between [0, 63]");
    switch(value) {
        // A = bb       --> current board
        // B = 1 << idx --> represents board of bits to flip
    case 0: {
        // A¬B
        bb &= ~((bitboard)0b1 << idx);
        break;
    }
    case 1: {
        // A+B
        bb |= ((bitboard)0b1 << idx);
        break;
    }
    }
}

int Piece::size(bitboard bb) {
    int size = 0;
    while(bb) {
        size += (bb & 1);
        bb >>= 1;
    }
    return size;
}

int Piece::makeMove(bitboard& bb_white, bitboard& bb_black, int& colorToMove, int index) {
    bitboard bb_piece = bb_white | bb_black;
    bitboard* playerBoard = Piece::white == colorToMove ? &bb_white : &bb_black;
    bitboard* opponentBoard = Piece::white == colorToMove ? &bb_black : &bb_white;
    // add piece
    Piece::set(*playerBoard, index, Piece::occupied);
    // flip pieces
    bitboard bb_flip = 0;
    for(int direction = 0; direction < (int)MoveData::moveOffsets.size(); ++direction) {
        bitboard bb_direction = 0;
        int offset = MoveData::moveOffsets[direction];
        for(int distance = offset; MoveData::distToEdge[index][direction]; distance += offset) {
            int target = index + distance;
            // empty tile, break
            if(Piece::at(bb_piece, target, Piece::empty)) break;
            // opponent piece, add to flip list
            else if(Piece::at(*opponentBoard, target, Piece::occupied)) {
                Piece::set(bb_direction, target, Piece::occupied);
                continue;
            }
            // player piece, break and flip this direction
            else if(Piece::at(*playerBoard, target, Piece::occupied)) {
                bb_flip |= bb_direction;
                break;
            }
            // loop exists on wall
        }
    }
    bb_white ^= bb_flip;
    bb_black ^= bb_flip;
    colorToMove = colorToMove == Piece::white ? Piece::black : Piece::white;
    // mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
    return index;
}

std::vector<int> Piece::toVector(bitboard bb) {
    std::vector<int> ret;
    for(int idx = 0; idx < bitboardSize; ++idx) {
        ret.insert(ret.begin(), (bb & 0b1));
        bb >>= 1;
    }
    return ret;
}

int Piece::moveToIndex(std::string move) {
    if(move.size() != 2) return -1;
    std::regex pattern("[a-h][1-8]");
    if(!std::regex_search(move, pattern)) return -1;
    // f5 == (5) + (3 * 8)
    return (fileToInt.at(move.at(0))) + (8 * rankToInt.at(move.at(1)));
}

std::string Piece::indexToMove(int index) {
    if(index < 0 || index > 64) return nullptr;
    return std::string(1, intToFile.at(index % 8)) + std::to_string(intToRank.at(index / 8));
}