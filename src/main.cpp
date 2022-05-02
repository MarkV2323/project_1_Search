#include <iostream>
#include "../header/printUI.h"
#include "../header/debug.h"
#include "../header/Node.h"
#include "../header/UniformSearch.h"
#include "../header/AStarSearch.h"

// Main Method of the program.
int main() {

    // Variables
    int userInput;

    // Objects
    Problem initProblem;
    Node* solution;

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
    // Print puzzle back to user.
    std::cout << "Your Puzzle: \n";
    initProblem.printInitialState(1);

    // Ask for algorithm.
    userInput = printUI::enterAlgorithm();
    // Handle user decision, run algorithm with desired settings entered above.
    switch (userInput) {
        case 1:
            // Run Uniform Cost Search.
            solution = UniformSearch::search(initProblem.move(Problem::NONE));
            if (solution == nullptr) {
                std::cout << "Uniform Cost Search has returned nullptr! Exiting now.";
                return -1;
            }
            // solution->getProblem()->printInitialState(1);
            solution->solution();
            break;
        case 2:
            // Run A* with Misplaced Tile heuristic.
            solution = AStarSearch::search1(initProblem.move(Problem::NONE));
            solution->solution();
            break;
        case 3:
            // Run A* with Euclidean Distance heuristic.
            solution = AStarSearch::search2(initProblem.move(Problem::NONE));
            solution->solution();
            break;
        default:
            return -1; // Something went wrong!
    }

    // Program has exited.
    return 0;
}
