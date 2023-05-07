#include "shortestpath.h"

int findNode(std::set<std::shared_ptr<Node>> set, std::shared_ptr<Node> node) {
    size_t i = 0;
    for (auto it = set.begin(); it != set.end(); it++) {
        if ((*it)->x == node->x && (*it)->y == node->y)
            return i;
        i++;
    }
    return -1;
}

std::vector<std::shared_ptr<Node>>
findShortestPath(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                 size_t xStart, size_t yStart, size_t xEnd, size_t yEnd) {

    if (vecBoard[xStart][yStart]->getState() == WALL) {
        std::cerr << "Error in shortest path: start is a wall" << std::endl;
        return {};
    }

    if (vecBoard[xEnd][yEnd]->getState() == WALL) {
        std::cerr << "Error in shortest path: end is a wall" << std::endl;
        return {};
    }

    if (xStart == xEnd && yStart == yEnd)
        return {};

    // define a lambda function for calculating the heuristic (Manhattan
    // distance)
    auto heuristic = [](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {
        return std::abs((int)a->x - (int)b->x) +
               std::abs((int)a->y - (int)b->y);
    };

    // initialize the open and closed sets
    std::set<std::shared_ptr<Node>> openSet;
    std::set<std::shared_ptr<Node>> closedSet;
    std::shared_ptr<Node> start =
        std::make_shared<Node>(Node({xStart, yStart, 0, nullptr}));
    std::shared_ptr<Node> end =
        std::make_shared<Node>(Node({xEnd, yEnd, 0, nullptr}));
    openSet.insert(start);

    // avoid infinite loop
    int maxDist = 0;

    // A* algorithm
    while (!openSet.empty()) {

        // get the node with the lowest f_score from the open set
        auto current = *openSet.begin();
        for (auto node : openSet) {
            if (node->distance + heuristic(node, end) <
                current->distance + heuristic(current, end))
                current = node;
        }

        // if the current node is the end node, it is the final path or if the
        // algorithm is stuck (bounded by CONVERGENCE)
        if ((current->x == end->x && current->y == end->y) ||
            maxDist > CONVERGENCE) {
            std::vector<std::shared_ptr<Node>> path;
            // pull up all the parents of the current node
            while (current) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // remove the current node from the open set and add it to the closed
        // set
        openSet.erase(current);
        closedSet.insert(current);

        // check the neighbors of the current node
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {

                // skip the current node and diagonals
                if ((i == 0 && j == 0) || (i != 0 && j != 0))
                    continue;

                // check all the neighbors
                size_t x = current->x + i;
                size_t y = current->y + j;

                if (x > 20 || y >= 26)
                    continue;
                if (vecBoard[x][y]->getState() == WALL)
                    continue;

                // create the neighbor node
                std::shared_ptr<Node> neighbor = std::make_shared<Node>(
                    Node{x, y, current->distance + 1, current});

                // if the neighbor is already in the closed set, skip it
                int index = findNode(closedSet, neighbor);
                if (index == -1) {
                    index = findNode(openSet, neighbor);
                    if (index != -1) {
                        // update the neighbor's distance if a shorter path
                        // was found
                        auto it = openSet.begin();
                        std::advance(it, index);
                        auto element = *it;
                        if ((*it)->distance > neighbor->distance) {
                            openSet.erase(it);
                            openSet.insert(neighbor);
                            maxDist = neighbor->distance;
                        }
                    } else {
                        openSet.insert(neighbor);
                        maxDist = neighbor->distance;
                    }
                }
            }
        }
    }

    // no path was found
    return {};
}

std::vector<std::vector<std::shared_ptr<square>>>
removeAboutTurn(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                dir _lastDir, size_t _xBoard, size_t _yBoard) {
    // avoid going back with modifying the behind square in a copy of
    // vecBoard
    std::vector<std::vector<std::shared_ptr<square>>> vecBoardCopy(
        vecBoard.size());
    for (size_t i = 0; i < vecBoard.size(); i++) {
        vecBoardCopy[i].resize(vecBoard[i].size());
        for (size_t j = 0; j < vecBoard[i].size(); j++) {
            vecBoardCopy[i][j] = std::make_shared<square>(*vecBoard[i][j]);
        }
    }

    switch (_lastDir) {
    case LEFT:
        vecBoardCopy[_xBoard + 1][_yBoard]->setState(WALL);
        break;
    case RIGHT:
        vecBoardCopy[_xBoard - 1][_yBoard]->setState(WALL);
        break;
    case UP:
        vecBoardCopy[_xBoard][_yBoard + 1]->setState(WALL);
        break;
    case DOWN:
        vecBoardCopy[_xBoard][_yBoard - 1]->setState(WALL);
        break;
    case NONE:
        break;
    }

    return vecBoardCopy;
}

dir findDir(std::shared_ptr<Node> A, std::shared_ptr<Node> B) {

    if (A == nullptr || B == nullptr) {
        std::cerr << "Empty node in findDir" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (B->parent != A) {
        std::cerr << "Nodes are not parent in findDir" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (A->x > B->x)
        return LEFT;

    else if (A->x < B->x)
        return RIGHT;

    else if (A->y > B->y)
        return UP;

    else if (A->y < B->y)
        return DOWN;

    else
        return NONE;
}

std::vector<dir>
findPossibleDir(std::vector<std::vector<std::shared_ptr<square>>> vecBoard,
                dir lastDir, dir avoidDir, size_t x, size_t y) {

    std::vector<dir> vecPossibleDir;

    if (lastDir != RIGHT) {

        if (avoidDir != RIGHT) {
            if (vecBoard[x - 1][y]->getState() == HALL)
                vecPossibleDir.push_back(LEFT);
        }
    }

    if (lastDir != LEFT) {

        if (avoidDir != RIGHT) {
            if (vecBoard[x + 1][y]->getState() == HALL)
                vecPossibleDir.push_back(RIGHT);
        }
    }

    if (lastDir != DOWN) {

        if (avoidDir != UP) {
            if (vecBoard[x][y - 1]->getState() == HALL)
                vecPossibleDir.push_back(UP);
        }
    }

    if (lastDir != UP) {

        if (avoidDir != DOWN) {
            if (vecBoard[x][y + 1]->getState() == HALL)
                vecPossibleDir.push_back(DOWN);
        }
    }

    return vecPossibleDir;
}