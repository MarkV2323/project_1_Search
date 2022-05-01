#ifndef EXAMPLEPROJECT_PROBLEM_H
#define EXAMPLEPROJECT_PROBLEM_H

/* Class definition for Problem Object.
 *
 * Problem represents the Problem Space of an 8 Puzzle.
 * It contains an initial state, operators, a goal state.
 *
 * We will represent our Initial and Goal states as the following data structure,
 * A 9 element integer array, each element indie relates the element's position on the 8 Puzzle Board,
 * IE: Element 5 relates to position 5 on the board (in 3x3 matrix form, tile 0 is the blank tile.)
 * [ 1 2 3]
 * [ 4 5 6] <-- (element 5 is in the middle of the board!)
 * [ 7 8 0] ^-- (Side note: This is the representation of the goal state on the board.)
 * Reasoning - 1D Arrays make it easy to perform operations on, and operations themselves don't cost much.
 *
 * Operations possible are (Blank = Tile 0):
 * 1) Blank move UP
 * 2) Blank move DOWN
 * 3) Blank move RIGHT
 * 4) Blank move LEFT
 *
 * We have one transition function named move, it will carry out the requested operation & return the new Problem.
 * Problem also comes with a printState Function, and a checkGoal Function.
 *
 */
class Problem {
private:
    // Directions Definition.
    enum Direction {UP, DOWN, LEFT, RIGHT};
    // underlying data structures for states.
    int initialState[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int goalState[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

public:
    // Constructors (Can build with default or passed initialState.)
    Problem();
    Problem(const int state[9]);

    // Destructor
    virtual ~Problem();

    // Transition Function
    // Should return itself if move is unsuccessful, otherwise return the new problem.
    // Should swap two elements of the initialState array based on Direction argument.
    Problem move(Direction);

    // Checks whether the initialState is equal to the goalState.
    bool checkGoal();

    // Prints out the initialState to the console.
    void printInitialState();

};

#endif //EXAMPLEPROJECT_PROBLEM_H
