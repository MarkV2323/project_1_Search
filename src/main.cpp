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

    // Begin program, start by introducing user and asking for type of 8 puzzle.
    userInput = printUI::printStart();
    debugInput(userInput);

    // Handle user decision and get our 8-puzzle.
    switch (userInput) {
        case 1:
            // Use default 8-puzzle.
            break;
        case 2:
            // Use user created 8-puzzle.
            break;
        default:
            return -1; // Something went wrong!
    }

    // Ask for algorithm.
    userInput = printUI::printStart();
    debugInput(userInput);

    // Handle user decision, run algorithm with desired settings entered above.
    switch (userInput) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            return -1; // Something went wrong!
    }

    // Program has exited.
    return 0;
}
