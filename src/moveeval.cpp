#include "../inc/moveeval.h"

// clang-format off
const int MoveEval::posVal[64] = {
     50,-20, 10,  4,  4, 10,-20, 50,
    -20,-50, -5, -2, -2, -5,-50,-20,
     10, -5, -3, -2, -2, -3, -5, 10,
      2, -2, -2, -1, -1, -2, -2,  2,
      2, -2, -2, -1, -1, -2, -2,  2,
     10, -5, -3, -2, -2, -3, -5, 10,
    -20,-50, -5, -2, -2, -5,-50,-20,
     50,-20, 10,  2,  2, 10,-20, 50,
};
// clang-format on

int MoveEval::getPosVal(const Board& board) {
    bitboard pieceBoard = board.getPieceBoard();
    bitboard colorBoard = board.getColorBoard();
    int color = board.getColorToMove();
    int val = 0;
    for (int idx = 0; idx < Board::boardSize; ++idx) {
        if (pieceBoard & (1ULL << idx)) {
            bitboard bb_PieceColor = colorBoard & (1ULL << idx);
            if (bb_PieceColor && color == Piece::white) {
                val += posVal[idx];
            } else {
                val -= posVal[idx];
            }
        }
    }
    return val;
}

int MoveEval::getMoveCountVal(const Board& board) {
    int val = 0;
    MoveGen mg(board.getPieceBoard(), board.getColorBoard(), board.getColorToMove());
    bitboard movesBoard = mg.getMoves();
    while (movesBoard) {
        val += ((movesBoard & 1) * moveCountVal);
        movesBoard >>= 1;
    }
    return board.getColorToMove() == Piece::white ? val : -val;
}

int MoveEval::getEval(const Board& b) {
    return getPosVal(b) + getMoveCountVal(b);
}
