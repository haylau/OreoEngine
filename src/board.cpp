/**
 * @file board.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../inc/board.h"

const std::map<char, int> Board::fileToInt = [] {
    std::map<char, int> files = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
    return files;
}();
const std::map<int, char> Board::intToFile = [] {
    std::map<int, char> files = {{0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'}};
    return files;
}();

Board::Board() {
    this->bb_piece = 0;
    this->bb_color = 0;

    initBoard();
}

Board::Board(std::vector<int> pieces) {
    this->bb_piece = 0;
    this->bb_color = 0;

    if(pieces.size() != 64) throw std::invalid_argument("Invalid Size");
    initBoard(pieces);
}

void Board::initBoard() {
    std::vector<int> startPieces;
    startPieces.insert(startPieces.end(), 27, 0);
    startPieces.push_back(Board::whitePiece);
    startPieces.push_back(Board::blackPiece);
    startPieces.insert(startPieces.end(), 6, 0);
    startPieces.push_back(Board::blackPiece);
    startPieces.push_back(Board::whitePiece);
    startPieces.insert(startPieces.end(), 27, 0);
    initBoard(startPieces);
}

void Board::initBoard(std::vector<int> pieces) {
    if(pieces.size() != 64) throw std::invalid_argument("Pieces must have 64 elements");
    for(const auto& piece : pieces) {
        bb_piece <<= 1;
        bb_piece |= Piece::piece(piece);
        bb_color <<= 1;
        bb_color |= Piece::color(piece);
    }
}

bitboard Board::getPieceBoard() const {
    return this->bb_piece;
}

bitboard Board::getColorBoard() const {
    return this->bb_color;
}

int Board::moveToIndex(std::string move) {
    if(move.size() != 2) throw std::invalid_argument("Invalid Size");
    std::regex pattern("[a-h][1-8]");
    if(!std::regex_search(move, pattern)) throw std::invalid_argument("Invalid Move");
    return (fileToInt.at(move.at(0)) - 1) + (8 * (std::stoi(std::string(1, move.at(1))) - 1));
}

std::string Board::indexToMove(int index) {
    if(index < 0 || index > 64) throw std::out_of_range("Invalid Index");
    return std::string(1, intToFile.at(index / 8)) + std::to_string(index % 8 + 1);
}