/**
 * @file movedata.h
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdexcept>
#include <array>

class MoveData {

private:
    MoveData(); // cannot be initalized     

public:
    static const std::array<int, 8> moveOffsets; // Clockwise from Up
    static const std::array<std::array<int, 8>, 64> distToEdge;
    static int dist(int from, int to);
};