#include "../header/printUI.h"

#include <iostream>

// Constructor
printUI::printUI() = default;

// Destructor
printUI::~printUI() = default;

// Implement functions
int printUI::printStart() {
    // Print introduction to the program, ask user to pick a puzzle to solve.
    std::cout << "Welcome to mvinc006's 8 Puzzle Solver!" << "\n";
    std::cout << "Press 1 for default puzzle, or 2 to enter your own puzzle." << "\n";

    // Gather input.
    // Basic idea here: force user to choose either 1 or 2, keep asking for input otherwise.
    int userInput = 0;
    do {
        std::cin >> userInput;
        // Error statement
        if (userInput != 1 && userInput != 2 || std::cin.fail()) {
            std::cout << "ERROR: YOU CAN ONLY PICK OPTION 1 or 2.\n";
            std::cin.clear();
            std::cin.ignore();
        }
    } while (userInput != 1 && userInput != 2);

    // return the 1 or 2 value, if 0 is returned something went wrong.
    return userInput;
}

void printUI::enterPuzzle() {

}

int printUI::enterAlgorithm() {
    return 0;
}
