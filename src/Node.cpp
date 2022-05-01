#include "../header/Node.h"
#include "iostream"

// Quick prints for action
inline void printAction(Problem::Direction action) {
    switch (action) {
        case 1:
            std::cout << "UP";
            break;
        case 2:
            std::cout << "DOWN";
            break;
        case 3:
            std::cout << "LEFT";
            break;
        case 4:
            std::cout << "RIGHT";
            break;
        case -1:
            std::cout << "NONE";
            break;
        default:
            break;
    }
}

// Get nodes path cost.
int Node::getPathCosts() {
    return this->pathCosts;
}

// Get nodes problem.
Problem *Node::getProblem() {
    return this->state;
}

// Child Node Function
Node *Node::childNode(Problem *problem, Node *parentC, Problem::Direction actionC) {
    // return the child.
    Node * child = new Node(problem->move(actionC), parentC, actionC, this->pathCosts + 1);
    return child;
}

// Solution Function
void Node::solution() {

    // Gets parent node.
    Node *curNode = this->parent;

    if (state == nullptr) {
        return;
    }

    // print info out on this node!
    std::cout << "NODE's ACTION: ";
    printAction(this->action);
    std::cout << " | PATH-COST = " << this->pathCosts << "\n";
    state->printInitialState(1);

    // Loop through parent nodes until nullptr is reached.
    while (curNode != nullptr) {
        if (curNode->state == nullptr) {
            return;
        }
        // print info out on this node!
        std::cout << "NODE's ACTION: ";
        printAction(curNode->action);
        std::cout << " | PATH-COST = " << curNode->pathCosts << "\n";
        curNode->state->printInitialState(1);

        // Move onto next parent.
        curNode = curNode->parent;
    }

}

// Constructor
Node::Node(Problem *problem, Node *parent, Problem::Direction action, int pathCosts) {
    this->state = problem;
    this->parent = parent;
    this->action = action;
    this->pathCosts = pathCosts;
}

// Deconstruct
Node::~Node() = default;