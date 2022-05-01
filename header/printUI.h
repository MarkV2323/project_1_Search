#ifndef EXAMPLEPROJECT_PRINTUI_H
#define EXAMPLEPROJECT_PRINTUI_H

/* Interface for printUI Object.
 *
 * Functions:
 * 1: printStart()  - Prints the starting introduction for the program.
 * 2: enterPuzzle() - Prints instructions on how to enter an 8 Puzzle.
 * 3: enterAlgorithm() - Prints instructions on how to select an Algorithm.
 *
 */
class printUI {

public:
    // Constructor
    printUI();

    // Destructor
    virtual ~printUI();

    // Functions
    static int printStart();
    void enterPuzzle();
    int enterAlgorithm();

};
#endif
