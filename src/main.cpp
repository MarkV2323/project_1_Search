#include <iostream>
#include "../header/printUI.h"

// Quick prints for userInput.
inline void debugInput(int userInput) {
    std::cout << "USER INPUT READ: " << userInput << "\n";
}

// Main Method of the program.
int main() {

    // Variables
    int userInput;

    // Objects
    printUI ui;
    Problem initProblem;

    // Begin program, start by introducing user and asking for type of 8 puzzle.
    userInput = printUI::printStart();
    debugInput(userInput);

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

    // Solve Default [ 1 2 0 4 5 3 7 8 6 ]
    initProblem.printInitialState(2);
    std::cout << "GOAL: " << initProblem.checkGoal() << "\n";
    initProblem.move(Problem::DOWN);
    initProblem.printInitialState(2);
    std::cout << "GOAL: " << initProblem.checkGoal() << "\n";
    initProblem.move(Problem::DOWN);
    initProblem.printInitialState(2);
    std::cout << "GOAL: " << initProblem.checkGoal() << "\n";

    // Ask for algorithm.
//    userInput = printUI::printStart();
//    debugInput(userInput);
//
//    // Handle user decision, run algorithm with desired settings entered above.
//    switch (userInput) {
//        case 1:
//            // Run Uniform Cost Search.
//            break;
//        case 2:
//            // Run A* with Misplaced Tile heuristic.
//            break;
//        case 3:
//            // Run A* with Euclidean Distance heuristic.
//            break;
//        default:
//            return -1; // Something went wrong!
//    }

    // Program has exited.
    return 0;
}
