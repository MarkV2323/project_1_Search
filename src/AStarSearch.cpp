#include <iostream>
#include "../header/AStarSearch.h"
// Lambda expression for frontier comparison
auto Compare = [](Node* a, Node* b) { return a->getPathCosts() > b->getPathCosts(); };
// check frontier function.
bool checkFrontier(std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> queue, Node* checkNode) {
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
            if (checkNode->getPathCosts() < currentNode->getPathCosts()) {
                // add checkNode to nodes list instead of popped node.
                std::cout << "ADDING CHECKNDOE TO NODES INSTEAD OF POPPED!\n";
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
bool checkExplored(std::set<Problem*> explored, Problem* checkProblem) {

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
AStarSearch::AStarSearch() = default;
AStarSearch::~AStarSearch() = default;

// Search Function
Node* AStarSearch::search1(Problem* problem) {
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


    return nullptr;
}

// Search Function
Node* AStarSearch::search2(Problem* problem) {
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


    return nullptr;
}
