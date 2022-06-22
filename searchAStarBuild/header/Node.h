#ifndef EXAMPLEPROJECT_NODE_H
#define EXAMPLEPROJECT_NODE_H
#include "Problem.h"
/**
 * Class definition for Node object.
 *
 * A node consist of the following:
 * - A pointer to a problem (can also be considered a "state")
 * - A pointer to a parent Node. (used for tracking)
 * - An action associated with the node (what it did)
 * - A path costs.
 *
 * A node should have two functions,
 * Child-Node - returns a child node from this node.
 * Solution - does a print trace of all parents of this node.
 */

class Node {
private:
    Problem * state;
    Node * parent;
    Problem::Direction action;
    int pathCosts;

public:
    // Default constructor, optional values.
    explicit Node(Problem *problem = nullptr, Node* parent = nullptr, Problem::Direction action = Problem::Direction::NONE,
                  int pathCosts = 0);

    virtual ~Node();

    Problem *getProblem();
    Node *childNode(Problem * problem, Node * parent, Problem::Direction action);
    int getPathCosts();
    void solution();

};
#endif //EXAMPLEPROJECT_NODE_H
