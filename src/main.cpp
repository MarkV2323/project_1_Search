#include <iostream>
#include "../header/printUI.h"
#include "../header/debug.h"

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
