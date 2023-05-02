#include "shortestpath.h"

std::vector<Node *>
findShortestPath(std::vector<std::vector<square *>> vecBoard, size_t xStart,
                 size_t yStart, size_t xEnd, size_t yEnd) {

    if (vecBoard[xStart][yStart]->getState() == WALL)
        return {};

    if (vecBoard[xEnd][yEnd]->getState() == WALL)
        return {};

    // define a lambda function for calculating the heuristic (Manhattan
    // distance)
    auto heuristic = [](Node *a, Node *b) {
        return std::abs((int)a->x - (int)b->x) +
               std::abs((int)a->y - (int)b->y);
    };

    // initialize the open and closed sets
    std::set<Node *> openSet;
    std::set<Node *> closedSet;
    Node *start = new Node{xStart, yStart, 0, nullptr};
    Node *end = new Node{xEnd, yEnd, 0, nullptr};
    openSet.insert(start);

    // avoid infinite loop
    int count = 0;

    // A* algorithm
    while (!openSet.empty() && count < 500) {

        // get the node with the lowest f_score from the open set
        auto current = *openSet.begin();
        for (auto node : openSet) {
            if (node->distance + heuristic(node, end) <
                current->distance + heuristic(current, end))
                current = node;
        }

        // fi the current node is the end node, it is the final path
        if (current->x == end->x && current->y == end->y) {
            std::vector<Node *> path;
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
                // Skip the current node and diagonals
                if ((i == 0 && j == 0) || (i != 0 && j != 0))
                    continue;

                size_t x = current->x + i;
                size_t y = current->y + j;

                if (x >= 20 || y >= 26)
                    continue;
                if (vecBoard[x][y]->getState() == WALL)
                    continue;

                // create a new node and add it to the open set if it hasn't
                // already been visited
                Node *neighbor = new Node{x, y, current->distance + 1, current};
                if (closedSet.find(neighbor) == closedSet.end()) {
                    auto it = openSet.find(neighbor);
                    if (it != openSet.end()) {
                        // update the neighbor's distance if a shorter path was
                        // found
                        if ((*it)->distance > neighbor->distance) {
                            openSet.erase(it);
                            openSet.insert(neighbor);
                        }
                    } else {
                        openSet.insert(neighbor);
                    }
                }
            }
        }

        count++;
    }

    // no path was found
    return {};
}

dir findDir(Node *A, Node *B) {

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