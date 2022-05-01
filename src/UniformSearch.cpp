#include <iostream>
#include "../header/UniformSearch.h"

// Constructor
UniformSearch::UniformSearch() {
    nodesCreated = 0;
}

// Search Function
Node* UniformSearch::search(Problem* problem) {
    // init return Node
    Node* node = new Node(problem);

    // init frontier with node as the only element.
    auto Compare = [](Node* a, Node* b) { return a->getPathCosts() > b->getPathCosts(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(Compare)> frontier(Compare);
    frontier.push(node);

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
            frontier.push(child);

            // std::cout << "MOVE: " << move << "\n";
        }
    } while (!frontier.empty()); // If frontier empty => return failure (nullptr)

    return nullptr;
}

