#include "../header/printUI.h"

#include <iostream>
#include <sstream>

// Constructor
printUI::printUI() = default;

// Destructor
printUI::~printUI() = default;

// Introduction UI
int printUI::printStart() {
    // Print introduction to the program, ask user to pick a puzzle to solve.
    std::cout << "Welcome to mvinc006's 8 Puzzle Solver!" << "\n";
    std::cout << "Press 1 for default puzzle, or 2 to enter your own puzzle.\n > ";

    // Gather input.
    // Basic idea here: force user to choose either 1 or 2, keep asking for input otherwise.
    int userInput = 0;
    std::string userString;

    do {
        // getLine and convert it to integer.
        std::getline(std::cin, userString);
        std::stringstream sStream(userString);
        if (sStream >> userInput) {
            // Error statement
            if (userInput != 1 && userInput != 2) {
                std::cout << "ERROR: YOU CAN ONLY PICK OPTION 1 or 2.\n >";
            }
        } else {
            std::cout << "ERROR: THAT IS NOT A NUMBER! TRY AGAIN.\n >";
        }
    } while (userInput != 1 && userInput != 2);

    // return the 1 or 2 value, if 0 is returned something went wrong.
    return userInput;
}

// Create Puzzle UI
Problem printUI::enterPuzzle() {
    // return value.
    Problem problem;
    int state[9];

    // Gather input.
    std::cout << "Enter 1D representation of Puzzle, use spaces between tiles. Ex: 1 2 3 4 5 6 7 8 0\n >";
    std::string userString;
    std::getline(std::cin, userString);

    // Parse String and transform into state[9].
    std::string tmpString;
    std::stringstream stringstream(userString); // Create string stream object.
    int index = 0;
    while (stringstream >> tmpString) {
        // errors based on index.
        if (index > 8) {
            std::cout << "ERROR: 1D REPRESENTATION TOO LONG. EXITING PROGRAM.";
            std::exit(-1);
        }
        // convert tmpString into int and assign into state.
        state[index] = std::stoi(tmpString);
        index += 1;
    }

    // errors based on index.
    if (index != 9) {
        std::cout << index << " | ERROR: 1D REPRESENTATION TOO SHORT. EXITING PROGRAM.";
        std::exit(-1);
    }

    // transform string data into problem.
    problem = Problem(state);

    // return user defined problem.
    return problem;
}

// Choose Algorithm UI
int printUI::enterAlgorithm() {

    // Gather input.
    std::cout << "Please choose from the following options,\n"
    << "1: Uniform Cost Search\n"
    << "2: A* with the Misplaced Tile heuristic\n"
    << "3: A* with the Euclidean Distance heuristic\n";

    int userInput = 0;
    std::string userString;

    do {
        // getLine and convert it to integer.
        std::getline(std::cin, userString);
        std::stringstream sStream(userString);
        if (sStream >> userInput) {
            // Error statement
            if (userInput != 1 && userInput != 2 && userInput != 3) {
                std::cout << "ERROR: YOU CAN ONLY PICK OPTION 1, 2 or 3.\n >";
            }
        } else {
            std::cout << "ERROR: THAT IS NOT A NUMBER! TRY AGAIN.\n >";
        }
    } while (userInput != 1 && userInput != 2 && userInput != 3);

    return userInput;

}
