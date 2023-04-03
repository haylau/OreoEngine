#include "../inc/engine.h"

std::size_t Engine::zhash(const Board& board, bitboard moves, int eval) {
    std::hash<std::string> hasher;
    std::string key = std::to_string(board.getPieceBoard()) + std::to_string(board.getColorBoard()) +
                      std::to_string(board.getColorToMove()) + std::to_string(moves) + std::to_string(eval);
    return hasher(key);
}

Engine::Engine() : numNodes(0), halfMoves(0), bestMove(-1) {}

int Engine::NegaMax(const Board& board, int depth, int alpha, int beta) {
    MoveGen mg(board.getPieceBoard(), board.getColorBoard(), board.getColorToMove());
    bitboard moves = mg.getMoves();

    if (this->halfMoves != 0) {
        std::size_t hash = zhash(board, moves, board.getColorToMove());
        auto it = transpositionTable.find(hash);
        if (it != transpositionTable.end()) {
            return it->second;
        }
        if (depth == 0) {
            int eval = MoveEval::getEval(board);
            transpositionTable[hash] = eval;
            return eval;
        }
    }

    int bound = alpha;
    int runningBestmove = -1;
    int index = 0;
    while (moves) {
        if (moves & 1) {
            ++this->halfMoves;
            // gen next board
            Board nextBoard(board);
            nextBoard.makeMove(index);
            // negamax
            int score = -1 * NegaMax(nextBoard, depth - 1, -beta, -alpha);
            --this->halfMoves;
            // hardfail
            if (score >= beta) {
                return beta;
            }
            // new best move
            if (score > alpha) {
                // increase lower bound
                alpha = score;
                if (this->halfMoves == 0) {
                    runningBestmove = index;
                }
            }
        }
        ++index;
        moves >>= 1;
    }
    if (bound != alpha) bestMove = runningBestmove;
    return alpha;
}

int Engine::getBestMove(int depth, const Board& board) {
    NegaMax(board, depth, MoveEval::blackVictory, MoveEval::whiteVictory);
    return this->bestMove;
}