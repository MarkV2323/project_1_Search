#include <iostream>
#include <math.h>
#include "../header/AStarSearch_euclidean.h"

int euclidean_dist1(int tile_val, int position) {
    // get tile position values
    int x_1;
    int y_1;
    // sets up position that the tile is currently at.
    switch (position) {
        case 0:
            // top left
            x_1 = 1;
            y_1 = 3;
            break;
        case 1:
            // top middle
            x_1 = 2;
            y_1 = 3;
            break;
        case 2:
            // top right
            x_1 = 3;
            y_1 = 3;
            break;
        case 3:
            // middle left
            x_1 = 1;
            y_1 = 2;
            break;
        case 4:
            // middle middle
            x_1 = 2;
            y_1 = 2;
            break;
        case 5:
            // middle right
            x_1 = 3;
            y_1 = 2;
            break;
        case 6:
            // bottom left
            x_1 = 1;
            y_1 = 1;
            break;
        case 7:
            // bottom middle
            x_1 = 2;
            y_1 = 1;
            break;
        case 8:
            // bottom right
            x_1 = 3;
            y_1 = 1;
            break;
        default:
            break;
    }
    // sets up position that the tile wants to be at.
    int x_2;
    int y_2;
    switch (tile_val) {
        case 1:
            // top left
            x_2 = 1;
            y_2 = 3;
            break;
        case 2:
            // top middle
            x_2 = 2;
            y_2 = 3;
            break;
        case 3:
            // top right
            x_2 = 3;
            y_2 = 3;
            break;
        case 4:
            // middle left
            x_2 = 1;
            y_2 = 2;
            break;
        case 5:
            // middle middle
            x_2 = 2;
            y_2 = 2;
            break;
        case 6:
            // middle right
            x_2 = 3;
            y_2 = 2;
            break;
        case 7:
            // bottom left
            x_2 = 1;
            y_2 = 1;
            break;
        case 8:
            // bottom middle
            x_2 = 2;
            y_2 = 1;
            break;
        case 0:
            // bottom right
            x_2 = 3;
            y_2 = 1;
            break;
        default:
            break;
    }
    // calculate distance
    // d = sqrt ( ( x_2 - x_1 ) ^ 2 + ( y_2 - y_1 ) ^ 2 )
    return sqrt(pow((x_2 - x_1), 2) + pow((y_2 - y_1), 2));
}

// Euclidean Distance Heuristic.
int heuristic1(Node* node) {
    // each tile has an euclidean distance from it's goal index.
    // all of these distances will be totaled, and then that will be our heuristic value.
    // first we need to get our current state and goal state as 1D representations, so we can compare.
    int *currentState = new int[9];
    node->getProblem()->getState(currentState);

    // Now we do a loop, calculating the euclidean distance for each tile.
    int euclidean_distance_heuristic = 0;

    for (int i = 0; i <= 8; i++) {
        euclidean_distance_heuristic += euclidean_dist1(currentState[i], i);
    }

    // free all 1D representations.
    free(currentState);

    // return count of misplaced tiles.
    return euclidean_distance_heuristic;
}

// Lambda expression for frontier comparison
auto Compare = [](Node* a, Node* b) {
    return (a->getPathCosts() + heuristic1(a)) > (b->getPathCosts() + heuristic1(b));
};

// check frontier function.
bool checkFrontier2(std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> queue, Node* checkNode) {
    // take queue, pop all nodes off and compare vs checkNode.
    // requeue all popped nodes (they will go back in order as they were)
    bool checkVal = false;
    Node* nodes[queue.size()]; // Array of Node*
    int nodeIndex = 0;
    Node* currentNode;

    // Will use checkNode state through checkFrontier, free at end before return.
    int *stateCheckNode = new int[9];
    checkNode->getProblem()->getState(stateCheckNode);

    // begin looping through queue.
    while (!queue.empty()) {
        currentNode = queue.top(); // get the current node.
        queue.pop();

        // compare current node vs checkNode.
        // will compare underlying 1D Array against each other to simplify things.
        // could probably have better comparison, but this will work.
        int *stateCurrentNode = new int[9];
        // store problem states
        currentNode->getProblem()->getState(stateCurrentNode);
        bool check = false;

        // check each tile against each other.
        for (int i = 0; i <= 8; i++) {
            if (stateCheckNode[i] != stateCurrentNode[i]) {
                // these states are NOT equal.
                check = false;
                break;
            } else {
                check = true;
            }
        }

        // free the allocated state memory as we no longer need it.
        free(stateCurrentNode);

        // if check is still true, then states are equal.
        if (check) {
            checkVal = true;

            // check if checkNode has lower path cost than currentNode.
            if ((checkNode->getPathCosts() + heuristic1(checkNode)) < (currentNode->getPathCosts() + heuristic1(currentNode))) {
                // add checkNode to nodes list instead of popped node.
                // std::cout << "ADDING CHECKNDOE TO NODES INSTEAD OF POPPED!\n";
                nodes[nodeIndex] = checkNode;
                nodeIndex++;
            }
            break; // exit queue popping loop.
        } else {
            // add popped node to nodes.
            nodes[nodeIndex] = currentNode;
            nodeIndex++;
        }

    }

    // free allocated checkNode state memory.
    free(stateCheckNode);

    // reconstruct pQueue
    for (int i = 0; i < nodeIndex; i++) {
        queue.push(nodes[i]);
    }

    // return
    return checkVal;
}
// check explored function.
bool checkExplored2(std::set<Problem*> explored, Problem* checkProblem) {

    bool checkVal = false;
    // Will use checkNode state through checkFrontier, free at end before return.
    int *stateCheck = new int[9];
    checkProblem->getState(stateCheck);

    // go through explored
    for (auto item : explored) {
        // check if item == checkProblem.
        int *stateItem = new int[9];
        item->getState(stateItem);
        // check each tile against each other.
        for (int i = 0; i <= 8; i++) {
            if (stateCheck[i] != stateItem[i]) {
                // these states are NOT equal.
                checkVal = false;
                break;
            } else {
                checkVal = true;
            }
        }
        if (checkVal) {
            // we found the item.
            return checkVal;
        }
    }

    // free
    free(stateCheck);
    // return
    return checkVal;
}

// Constructor and Destructor
AStarSearch_euclidean::AStarSearch_euclidean() = default;
AStarSearch_euclidean::~AStarSearch_euclidean() = default;

// Search Function
Node* AStarSearch_euclidean::search(Problem* problem) {
    // init return Node
    Node* node = new Node(problem);

    // init frontier with node as the only element.
    std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> frontier(Compare);
    frontier.push(node);
    int nodesCreated = 1;
    int maxQueueSize = 1;

    // init empty set.
    std::set<Problem*> explored;

    // our possible move list
    Problem::Direction moves[4];

    // begin looping.
    do {
        /* choose lowest-cost node in frontier */
        node = frontier.top();
        frontier.pop();

        /* perform a goal test on this node */
        if (node->getProblem()->checkGoal()) {
            // print quick stats on search.
            std::cout << "Total Nodes created during Search: " << nodesCreated << "\n";
            std::cout << "Max Size of priority queue at any time: " << maxQueueSize << "\n";
            // return solution node.
            return node;
        }

        /* add node's problem to explored nodes */
        explored.insert(node->getProblem());

        /* for each loop based on possible moves.*/
        node->getProblem()->getAllMoves(moves);
        for (Problem::Direction move : moves) {
            if (move == -1) {
                continue; // Skip this illegal move.
            }

            Node* child;
            if (move == 1) {
                // UP act
                child = node->childNode(node->getProblem(), node, Problem::UP);
            } else if (move == 2) {
                // DOWN act
                child = node->childNode(node->getProblem(), node, Problem::DOWN);
            } else if (move == 3) {
                // LEFT act
                child = node->childNode(node->getProblem(), node, Problem::LEFT);
            } else if (move == 4) {
                // RIGHT act
                child = node->childNode(node->getProblem(), node, Problem::RIGHT);
            }

            // TODO: Check if this child is in explored or frontier
            if (!checkFrontier2(frontier, child) && !checkExplored2(explored, child->getProblem())) {
                frontier.push(child); // Push child as it's not in frontier or explored.
                // the heuristic is added during the push to calculate the nodes position in the queue.
                // statics
                nodesCreated++;
                if (frontier.size() > maxQueueSize) {
                    maxQueueSize = frontier.size();
                }
            } // child.state in frontier with higher path cost handled in checkFrontier function itself!

            // std::cout << "MOVE: " << move << "\n";
        }
//        std::cout << "Total Nodes created during Search: " << nodesCreated << "\n";
//        std::cout << "Max Size of priority queue at any time: " << maxQueueSize << "\n";
    } while (!frontier.empty()); // If frontier empty => return failure (nullptr)

    return nullptr;
}

