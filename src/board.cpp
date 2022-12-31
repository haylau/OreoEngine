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
Board::Board(bitboard bb_white, bitboard bb_black, int colorToMove)
    : bb_white(bb_white), bb_black(bb_black), colorToMove(colorToMove) {
    this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
}
Board::Board(bitboard bb_white, bitboard bb_black, bitboard bb_moves, int colorToMove)
    : bb_white(bb_white), bb_black(bb_black), colorToMove(colorToMove) {
    this->mg = MoveGen(this->bb_white, this->bb_black, bb_moves, this->colorToMove);
}
Board::Board(const Board& b) {
    this->bb_white = b.bb_white;
    this->bb_black = b.bb_black;
    this->colorToMove = b.colorToMove;
    this->mg = MoveGen(b.bb_white, b.bb_black, b.getMoves(), b.colorToMove);
}
Board::Board(const Board& b, int moveIdx) {
    this->bb_white = b.bb_white;
    this->bb_black = b.bb_black;
    this->colorToMove = b.colorToMove;
    this->makeMove(moveIdx);
    this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
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
};
void Board::initBoard(std::vector<int> pieces) {
    if(pieces.size() != 64) throw std::invalid_argument("Pieces must have 64 elements");
    // init white and black boards
    std::reverse(pieces.begin(), pieces.end());
    for(const auto& piece : pieces) {
        this->bb_white <<= 1;
        this->bb_black <<= 1;
        if(piece == Piece::whitePiece) bb_white |= 1;
        if(piece == Piece::blackPiece) bb_black |= 1;
    }
    // calc legal moves
    this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
}

bitboard Board::getWhiteBoard() const {
    return this->bb_white;
}

bitboard Board::getBlackBoard() const {
    return this->bb_black;
}

bitboard Board::getMoves() const {
    return this->mg.getMoves();
}

int Board::getColorToMove() const {
    return this->colorToMove;
}

int Board::makeMove(std::string move) {
    return makeMove(Piece::moveToIndex(move));
}

int Board::makeMove(int index) {
    if(Piece::at(this->getMoves(), index, Piece::empty)) return -1; // illegal move
    int ret = Piece::makeMove(this->bb_white, this->bb_black, this->colorToMove, index);
    this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
    if(Piece::size(this->mg.getMoves()) == 0) {
        // player has no moves, skip turn
        this->colorToMove = this->colorToMove == Piece::white ? Piece::black : Piece::white;
        this->mg = MoveGen(this->bb_white, this->bb_black, this->colorToMove);
        if(Piece::size(this->mg.getMoves()) == 0) {
            // both players have no moves --> game over!
            return Board::gameOver;
        }
        return Board::skipTurn;
    }
    return ret;
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