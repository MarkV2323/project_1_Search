#include <iostream>
#include "../header/AStarSearch_misplaced.h"

// Misplaced Tile Heuristic.
int heuristic(Node* node) {
    // each misplaced tile counts as an additional path cost of 1.
    // first we need to get our current state and goal state as 1D representations, so we can compare.
    int *currentState = new int[9];
    node->getProblem()->getState(currentState);
    int *goalState = new int[9];
    node->getProblem()->getGoalState(goalState);

    // Now we do a loop and compare the two, keeping track of each misplaced tiles.
    int misplaced_tile = 0;

    for (int i = 0; i <= 8; i++) {
        if (currentState[i] != goalState[i]) {
            misplaced_tile++;
        }
    }

    // free all 1D representations.
    free(currentState);
    free(goalState);

    // return count of misplaced tiles.
    return misplaced_tile;
}

// Lambda expression for frontier comparison
auto Compare = [](Node* a, Node* b) {
    return (a->getPathCosts() + heuristic(a)) > (b->getPathCosts() + heuristic(b));
};

// check frontier function.
bool checkFrontier1(std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> queue, Node* checkNode) {
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
            if ((checkNode->getPathCosts() + heuristic(checkNode)) < (currentNode->getPathCosts() + heuristic(currentNode))) {
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
bool checkExplored1(std::set<Problem*> explored, Problem* checkProblem) {

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
AStarSearch_misplaced::AStarSearch_misplaced() = default;
AStarSearch_misplaced::~AStarSearch_misplaced() = default;

// Search Function
Node* AStarSearch_misplaced::search(Problem* problem) {
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
            if (!checkFrontier1(frontier, child) && !checkExplored1(explored, child->getProblem())) {
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

