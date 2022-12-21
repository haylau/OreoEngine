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
}

Board::Board(std::vector<int> pieces) {
    if(pieces.size() > 64) throw std::invalid_argument("pieces has more than 64 pieces.");
    for(const auto& piece : pieces) {
        bb_piece |= Piece::piece(piece);
        bb_piece <<= 1;
        
        bb_color |= Piece::color(piece);
        bb_color <<= 1;

    }
}