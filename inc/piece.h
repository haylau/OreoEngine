/**
 * @file piece.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */


class Piece {

private:

    // 1 = tile has piece / 0 = tile does not have piece
    static const char pieceMask = 0b00000001; 
    // 1 = white / 0 = black
    static const char colorMask = 0b00000010; 

public:
    static const int isEmpty = 0; 
    static const int isPiece = 1;
    static const int black = 0;
    static const int white = 1;

    static int color(int piece);
    static bool piece(int piece);

};