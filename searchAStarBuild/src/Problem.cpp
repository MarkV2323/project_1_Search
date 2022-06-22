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
Problem* Problem::move(Direction direction) {

    // return problem.
    Problem *problem;

    // Make copy of initialState.
    int copyState[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i <= 8; i++) {
        copyState[i] = initialState[i];
    }

    // get position on board.
    int pos = getPosition();
    // store new position.
    int np = -1;

    // attempt to move.
    switch (direction) {
        case NONE:
            // return pointer of itself by not moving.
            break;
        case UP:
            // check for illegal move.
            if (pos == 0 || pos == 1 || pos == 2) {
                // illegal move return false!
                return nullptr;
            }
            // perform the move operation.
            // Formula for new position: NP = pos - 3.
            np = pos - 3; // calc new pos
            copyState[np] = initialState[pos]; // swap state[pos] into copyState[np]
            copyState[pos] = initialState[np]; // place state[np] into copyState[pos]
            break;
        case DOWN:
            // check for illegal move.
            if (pos == 6 || pos == 7 || pos == 8) {
                // illegal move return false!
                return nullptr;
            }
            // perform the move operation.
            // Formula for new position: NP = pos + 3.
            np = pos + 3; // calc new pos
            copyState[np] = initialState[pos]; // swap state[pos] into copyState[np]
            copyState[pos] = initialState[np]; // place state[np] into copyState[pos]
            break;
        case LEFT:
            // check for illegal move.
            if (pos == 0 || pos == 3 || pos == 6) {
                // illegal move return false!
                return nullptr;
            }
            // perform the move operation.
            // Formula for new position: NP = pos - 1.
            np = pos - 1; // calc new pos
            copyState[np] = initialState[pos]; // swap state[pos] into copyState[np]
            copyState[pos] = initialState[np]; // place state[np] into copyState[pos]
            break;
        case RIGHT:
            // check for illegal move.
            if (pos == 2 || pos == 5 || pos == 8) {
                // illegal move return false!
                return nullptr;
            }
            // perform the move operation.
            // Formula for new position: NP = pos + 1.
            np = pos + 1; // calc new pos
            copyState[np] = initialState[pos]; // swap state[pos] into copyState[np]
            copyState[pos] = initialState[np]; // place state[np] into copyState[pos]
            break;
        default:
            return nullptr;
    }

    // move must have been legal and worked (or didn't move).
    // package a new Problem up with the copyState.
    problem = new Problem(copyState);
    return problem;

}

// getAllMoves Function
// CAN ACCESS DIRECTIONS IN POINTER VIA,
// moves[index]
void Problem::getAllMoves(Direction *moves) {

    // Start by being able to move in all directions.
    moves[0] = UP;
    moves[1] = DOWN;
    moves[2] = LEFT;
    moves[3] = RIGHT;

    // get position on board.
    int pos = getPosition();

    // Checks for illegal moves.
    if (pos == 0 || pos == 1 || pos == 2) {
        // cannot move UP.
        moves[0] = NONE;
    }
    if (pos == 6 || pos == 7 || pos == 8) {
        // cannot move DOWN.
        moves[1] = NONE;
    }
    if (pos == 0 || pos == 3 || pos == 6) {
        // cannot move LEFT.
        moves[2] = NONE;
    }
    if (pos == 2 || pos == 5 || pos == 8) {
        // cannot move RIGHT.
        moves[3] = NONE;
    }

}

// getState Function
// CAN ACCESS TILES IN POINTER VIA,
// state[index]
void Problem::getState(int *state) {
    // begin mapping initialState onto state array passed in.
    for (int i = 0; i <= 8; i++) {
        state[i] = initialState[i];
    }
}

void Problem::getGoalState(int *state) {
    // begin mapping goalState onto state array passed in.
    for (int i = 0; i <= 8; i++) {
        state[i] = goalState[i];
    }
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
