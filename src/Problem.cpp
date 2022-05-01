#include "iostream"
#include "../header/Problem.h"

// PRIVATE UTIL FUNCTION:
int Problem::getPosition() {
    for (int i = 0; i <= 8; i++) {
        if (initialState[i] == 0) {
            return i;
        }
    }
    return -1;
}

// PUBLIC:
// Transition Function
bool Problem::move(Direction direction) {

    // return problem.
    Problem problem;

    // get position on board.
    int pos = getPosition();
    // tmp store value at swap position.
    int tmp = 0;
    // store new position.
    int np = -1;

    // attempt to move.
    switch (direction) {
        case UP:
            // check for illegal move.
            if (pos == 0 || pos == 1 || pos == 2) {
                // illegal move return false!
                return false;
            }
            // perform the move operation.
            // Formula for new position: NP = pos - 3.
            np = pos - 3; // calc new pos
            tmp = initialState[np]; // store tmp val at np.
            initialState[np] = initialState[pos]; // swap state[pos] into state[np]
            initialState[pos] = tmp; // place tmp into state[pos]
            break;
        case DOWN:
            // check for illegal move.
            if (pos == 6 || pos == 7 || pos == 8) {
                // illegal move return false!
                return false;
            }
            // perform the move operation.
            // Formula for new position: NP = pos + 3.
            np = pos + 3; // calc new pos
            tmp = initialState[np]; // store tmp val at np.
            initialState[np] = initialState[pos]; // swap state[pos] into state[np]
            initialState[pos] = tmp; // place tmp into state[pos]
            break;
        case LEFT:
            // check for illegal move.
            if (pos == 0 || pos == 3 || pos == 6) {
                // illegal move return false!
                return false;
            }
            // perform the move operation.
            // Formula for new position: NP = pos - 1.
            np = pos - 1; // calc new pos
            tmp = initialState[np]; // store tmp val at np.
            initialState[np] = initialState[pos]; // swap state[pos] into state[np]
            initialState[pos] = tmp; // place tmp into state[pos]
            break;
        case RIGHT:
            // check for illegal move.
            if (pos == 2 || pos == 5 || pos == 8) {
                // illegal move return false!
                return false;
            }
            // perform the move operation.
            // Formula for new position: NP = pos + 1.
            np = pos + 1; // calc new pos
            tmp = initialState[np]; // store tmp val at np.
            initialState[np] = initialState[pos]; // swap state[pos] into state[np]
            initialState[pos] = tmp; // place tmp into state[pos]
            break;
        default:
            return false;
    }

    // move must have been legal and worked, return true.
    return true;
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
void Problem::printInitialState(int ver) {
    // print version (DEFAULT is 1D representation)
    if (ver == 0) {
        std::cout << "[ ";
        for (int i = 0; i <= 8; i++) {
            std::cout << initialState[i] << " ";
        }
        std::cout << "]\n";
    } else {
        // Board representation.
        std::cout << "[ " << initialState[0] << " " << initialState[1] << " " << initialState[2] << " ]\n";
        std::cout << "[ " << initialState[3] << " " << initialState[4] << " " << initialState[5] << " ]\n";
        std::cout << "[ " << initialState[6] << " " << initialState[7] << " " << initialState[8] << " ]\n";
    }
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
