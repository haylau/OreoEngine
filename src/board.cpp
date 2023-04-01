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

Board::Board() 
    : bb_piece(0ULL), bb_color(0ULL), colorToMove(Piece::white) {
    initBoard();
}

Board::Board(std::vector<int> pieces) 
    : bb_piece(0ULL), bb_color(0ULL), colorToMove(Piece::white) {
    if(pieces.size() != 64) throw std::invalid_argument("Invalid Size");
    initBoard(pieces);
}

Board::Board(const Board& other) 
    : bb_piece(other.bb_piece), bb_color(other.bb_color), colorToMove(other.colorToMove) {}

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

int Board::getColorToMove() const {
    return this->colorToMove;
}

void Board::setColorToMove(int color) {
    if(color != Piece::white && color != Piece::black) throw std::invalid_argument("Invalid Color");
    this->colorToMove = color;
}

bool Board::isComplete() const {
    return bb_piece == Board::finishedGame;
}

int Board::getWinner() const {
    int whiteCount = 0;
    int blackCount = 0;
    bitboard pieceBoard = getPieceBoard();
    bitboard colorBoard = getColorBoard();
    while(pieceBoard != 0ULL) {
        if(pieceBoard & 1ULL) {
            if(colorBoard & 1ULL) {
                blackCount++;
            }
            else {
                whiteCount++;
            }
        }
        pieceBoard >>= 1;
        colorBoard >>= 1;
    }
    if(whiteCount == blackCount) return Board::draw;
    return whiteCount > blackCount ? Piece::white : Piece::black;
}

int Board::moveToIndex(std::string move) {
    if(move.size() != 2) throw std::invalid_argument("Invalid Size");
    std::regex pattern("[a-h][1-8]");
    if(!std::regex_search(move, pattern)) throw std::invalid_argument("Invalid Move");
    return fileToInt.at(move.at(0)) + (8 * (std::stoi(std::string(1, move.at(1))) - 1));
}

std::string Board::indexToMove(int index) {
    if(index < 0 || index > 63) throw std::out_of_range("Invalid Index");
    return std::string(1, intToFile.at(index % 8)) + std::to_string(index / 8 + 1);
}

bool Board::makeMove(std::string move) {
    int index;
    try {
        index = moveToIndex(move);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return makeMove(index);
}

bool Board::makeMove(int index) {
    MoveGen mg = MoveGen(getPieceBoard(), getColorBoard(), getColorToMove());
    bitboard moves = mg.getMoves();

    // no legal moves for either player
    if(moves == 0ULL) {
        return false;
    }

    if(!(moves & (1ULL << index))) {
        std::cerr << "Invalid Move" << std::endl;
        return false;
    }

    if(getColorToMove() == Piece::white) {
        bb_color |= (1ULL << index);
    }
    bb_piece |= (1ULL << index);

    for(int dir = 0; dir < (int)MoveData::moveOffsets.size(); ++dir) {
        bitboard flip = 0ULL;
        for(int dist = 1; dist < MoveData::distToEdge[index][dir]; ++dist) {
            if(bb_piece & (1ULL << (index + dist * MoveData::moveOffsets[dir]))) {
                bitboard bb_PieceColor = bb_color & (1ULL << (index + dist * MoveData::moveOffsets[dir]));
                if((bb_PieceColor && getColorToMove() == Piece::black) || (!bb_PieceColor && getColorToMove() == Piece::white)) {
                    flip |= (1ULL << (index + dist * MoveData::moveOffsets[dir]));
                }
                else {
                    bb_color ^= flip;
                    break;
                }
            }
            else {
                break;
            }
        }
    }

    mg = MoveGen(getPieceBoard(), getColorBoard(), getColorToMove());
    moves = mg.getMoves();

    // check for skip
    if(moves != 0ULL) {
        this->colorToMove = getColorToMove() == Piece::white ? Piece::black : Piece::white;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {

    std::string border = "+---+---+---+---+---+---+---+---+";
    bitboard pieceBoard = board.getPieceBoard();
    bitboard colorBoard = board.getColorBoard();

    MoveGen mg(board.getPieceBoard(), board.getColorBoard(), board.getColorToMove());
    bitboard movesBoard = mg.getMoves();

    os << border << std::endl;
    for(int i = 0; i < 8; i++) {
        os << "|";
        for(int j = 0; j < 8; j++) {
            int index = i * 8 + j;
            char piece = '-';
            if((pieceBoard & (1ULL << index)) != 0) {
                if((colorBoard & (1ULL << index)) != 0) {
                    piece = 'W';
                } else {
                    piece = 'B';
                }
            }
            else if((movesBoard & (1ULL << index)) != 0) {
                piece = 'o';
            }
            os << " " << piece << " |";
        }
        os << " " << (i + 1) << std::endl << border << std::endl;
    }
    os << "  a   b   c   d   e   f   g   h" << std::endl;
    return os;
}
