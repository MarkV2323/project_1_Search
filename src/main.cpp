#include <iostream>
#include "../header/printUI.h"
#include "../header/debug.h"
#include "../header/Node.h"

void debug() {
    // debug Problem
    Problem initProblem = Problem();
    //initProblem.printInitialState(1);
    Problem::Direction moves[4];
    initProblem.getAllMoves(moves);
    // debugMoves(moves);
    Problem * m1 = initProblem.move(Problem::NONE);
    m1->printInitialState(1);
    std::cout << "\nSTARTING NODE DEBUG!\n";
    // debug Node, start off by handing over initProblem that doesn't move, so it gives a pointer.
    Node *node1 = new Node(m1);
    Node *node2 = node1->childNode(node1->getProblem(), node1, Problem::Direction::DOWN);
    Node *node3 = node2->childNode(node2->getProblem(), node2, Problem::Direction::DOWN);
    Node *node4 = node3->childNode(node3->getProblem(), node3, Problem::Direction::LEFT);
    node4->solution();
    free(node4);
    free(node3);
    free(node2);
    free(node1);
    free(m1);
}

// Main Method of the program.
int main() {

    // Variables
    int userInput;

    // Objects
    Problem initProblem;

    // Begin program, start by introducing user and asking for type of 8 puzzle.
    userInput = printUI::printStart();
    // Handle user decision and get our 8-puzzle.
    switch (userInput) {
        case 1:
            // Use default 8-puzzle.
            initProblem = Problem();
            break;
        case 2:
            // Use user created 8-puzzle.
            initProblem = printUI::enterPuzzle();
            break;
        default:
            return -1; // Something went wrong!
    }

    // Ask for algorithm.
    userInput = printUI::enterAlgorithm();
    // Handle user decision, run algorithm with desired settings entered above.
    switch (userInput) {
        case 1:
            // Run Uniform Cost Search.
            break;
        case 2:
            // Run A* with Misplaced Tile heuristic.
            break;
        case 3:
            // Run A* with Euclidean Distance heuristic.
            break;
        default:
            return -1; // Something went wrong!
    }

    // Program has exited.
    return 0;
}
