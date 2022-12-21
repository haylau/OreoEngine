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
    startPieces.push_back(Piece::whitePiece);
    startPieces.push_back(Piece::blackPiece);
    startPieces.push_back(Piece::whitePiece);
    startPieces.push_back(Piece::blackPiece);
    startPieces.insert(startPieces.end(), 27, 0);
    initBoard(startPieces);
}

void Board::initBoard(std::vector<int> pieces) {
    for(const auto& piece : pieces) {
        bb_piece <<= 1;
        bb_piece |= Piece::piece(piece);
        bb_color <<= 1;
        bb_color |= Piece::color(piece);
    }
}

int Board::moveToIndex(std::string move) {
    if(move.size() != 2) throw std::invalid_argument("Invalid Size");
    std::regex pattern("[a-h][1-8]");
    if(!std::regex_search(move, pattern)) throw std::invalid_argument("Invalid Move");
    return (files.at(move.at(0)) - 1) + (8 * (std::stoi(std::string(1, move.at(1))) - 1));
}

std::string Board::indexToMove(int index) {
    if(index < 0 || index > 64) throw std::out_of_range("Invalid Index");
    return "" + files.at(index/8) + index % 8 + 1;
}