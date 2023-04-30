#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "lib.h"
#include "square.h"
#include <algorithm>
#include <set>

struct Node {
    size_t x;
    size_t y;
    int distance;
    Node *parent;
};

/**
 * @brief Find the shortest path between two positions using A* algorithm with
 * Manhattan Heuristic.
 *
 * @param vecBoard
 * @param xStart
 * @param yStart
 * @param xEnd
 * @param yEnd
 * @return std::vector<Node *>
 */
std::vector<Node *>
findShortestPath(std::vector<std::vector<square *>> vecBoard, size_t xStart,
                 size_t yStart, size_t xEnd, size_t yEnd);

/**
 * @brief Find the direction to take to go from A to B.
 *
 * @param A
 * @param B
 * @return dir
 */
dir findDir(Node *A, Node *B);

#endif