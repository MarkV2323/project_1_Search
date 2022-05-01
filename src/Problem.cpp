#include "iostream"
#include "../header/Problem.h"

// Transition Function
Problem Problem::move(Direction) {
    // STUB
    return *this;
}

// CheckGoal Function
bool Problem::checkGoal() {
    for (int i = 0; i <= 8; i++) {
        if (initialState[i] != goalState[i]) {
            return false;
        }
    }
    return true;
}

// printInitialState Function (prints vertically, in 1D array form)
void Problem::printInitialState() {
    std::cout << "[ ";
    for (int i = 0; i <= 8; i++) {
        std::cout << initialState[i] << " ";
    }
    std::cout << "]\n";
}

// Constructors
Problem::Problem() {
    // DEFAULT (Easy Test Case)
    initialState[0] = 1;
    initialState[1] = 2;
    initialState[2] = 0;
    initialState[3] = 4;
    initialState[4] = 5;
    initialState[5] = 3;
    initialState[6] = 7;
    initialState[7] = 8;
    initialState[8] = 6;
}

Problem::Problem(const int state[9]) {
    // User defined state.
    for (int i = 0; i <= 8; i++) {
        initialState[i] = state[i]; // Direct Assignment.
    }
}

// Deconstruct
Problem::~Problem() = default;
