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

// Board Implementation
Board::Board() {
    this->bb_white = 0b0;
    this->bb_black = 0b0;
    this->colorToMove = Piece::white;
    initBoard();
}

Board::Board(std::vector<int> pieces) {
    this->bb_white = 0b0;
    this->bb_black = 0b0;
    // #TODO determine turn based on num of pieces
    this->colorToMove = Piece::white;
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
;
void Board::initBoard(std::vector<int> pieces) {
    if(pieces.size() != 64) throw std::invalid_argument("Pieces must have 64 elements");
    std::reverse(pieces.begin(), pieces.end());
    for(const auto& piece : pieces) {
        this->bb_white <<= 1;
        this->bb_black <<= 1;
        if(piece == Piece::whitePiece) bb_white |= 1;
        if(piece == Piece::blackPiece) bb_black |= 1;
    }
    this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
}

bitboard Board::getWhiteBoard() const {
    return this->bb_white;
}

bitboard Board::getBlackBoard() const {
    return this->bb_black;
}

int Board::getColorToMove() const {
    return this->colorToMove;
}

int Board::makeMove(std::string move) {
    return makeMove(Piece::moveToIndex(move));
}

int Board::makeMove(int index) {
    if(Piece::at(this->mg.getMoves(), index, Piece::empty)) return -1; // illegal move
    bitboard bb_piece = this->bb_white | this->bb_black;
    bitboard* playerBoard = Piece::white == this->colorToMove ? &this->bb_white : &this->bb_black;
    bitboard* opponentBoard = Piece::white == this->colorToMove ? &this->bb_black : &this->bb_white;
    // add piece
    Piece::set(*playerBoard, index, Piece::occupied);
    // flip pieces
    bitboard bb_flip = 0;
    for(int direction = 0; direction < (int)MoveData::moveOffsets.size(); ++direction) {
        bitboard bb_direction = 0;
        int offset = MoveData::moveOffsets[direction];
        for(int distance = offset; MoveData::distToEdge[direction][index]; distance += offset) {
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
    this->bb_white ^= bb_flip;
    this->bb_black ^= bb_flip;
    this->colorToMove = this->colorToMove == Piece::white ? Piece::black : Piece::white;
    this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
    return index;
}

std::ostream& operator<<(std::ostream& os, const Board& b) {

    auto whitePieces = Piece::toVector(b.getWhiteBoard());
    auto blackPieces = Piece::toVector(b.getBlackBoard());
    auto moves = Piece::toVector(b.mg.getMoves());

    auto getPiece = [&](int index) -> std::string {
        if(whitePieces[index] == 1) return "w";
        if(blackPieces[index] == 1) return "b";
        if(moves[index] == 1) return "x";
        return " ";
    };

    for(int i = 8; i >= 1; --i) {
        std::string a = getPiece(i * 8 - 1);
        std::string b = getPiece(i * 8 - 2);
        std::string c = getPiece(i * 8 - 3);
        std::string d = getPiece(i * 8 - 4);
        std::string e = getPiece(i * 8 - 5);
        std::string f = getPiece(i * 8 - 6);
        std::string g = getPiece(i * 8 - 7);
        std::string h = getPiece(i * 8 - 8);

        os << "+---+---+---+---+---+---+---+---+\n";
        os << "| " << a << " | " << b << " | " << c << " | " << d << " | " << e << " | " << f << " | " << g << " | "
           << h << " | " << i << " \n";
    }
    os << "+---+---+---+---+---+---+---+---+\n";
    os << "  a   b   c   d   e   f   g   h\n";
    return os;
}