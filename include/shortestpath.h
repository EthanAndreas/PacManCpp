#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "lib.h"
#include "square.h"
#include <algorithm>
#include <set>

#define CONVERGENCE 300

struct Node {
    size_t x;
    size_t y;
    int distance;
    std::shared_ptr<Node> parent;
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
 * @return std::vector<std::shared_ptr<Node>>
 */

std::vector<std::shared_ptr<Node>>
findShortestPath(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                 size_t xStart, size_t yStart, size_t xEnd, size_t yEnd);

/**
 * @brief Make a new vecBoard without the possibility to go back for the
 * calculation of the shortest path.
 *
 * @param vecBoard
 * @param _lastDir
 * @param _xBoard
 * @param _yBoard
 * @return std::vector<std::vector<std::shared_ptr<square>>>
 */
std::vector<std::vector<std::shared_ptr<square>>>
removeAboutTurn(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                dir _lastDir, size_t _xBoard, size_t _yBoard);

/**
 * @brief Find the direction to take to go from A to B.
 *
 * @param A
 * @param B
 * @return dir
 */
dir findDir(std::shared_ptr<Node> A, std::shared_ptr<Node> B);

/**
 * @brief Find the possible directions caracter can take with avoiding a
 * special direction and avoid going back.
 *
 * @param vecBoard
 * @param lastDir
 * @param avoidDir
 * @param x
 * @param y
 */
std::vector<dir>
findPossibleDir(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                dir lastDir, dir avoidDir, size_t x, size_t y);

#endif