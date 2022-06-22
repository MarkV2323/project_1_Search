#ifndef EXAMPLEPROJECT_PRINTUI_H
#define EXAMPLEPROJECT_PRINTUI_H

#include "Problem.h"

/* Class definition for printUI.
 *
 * Functions (All static, no object needed):
 * 1: printStart()  - Prints the starting introduction for the program.
 * 2: enterPuzzle() - Prints instructions on how to enter an 8 Puzzle, return problem representation.
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
    static Problem enterPuzzle();
    static int enterAlgorithm();

};
#endif
