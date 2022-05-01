#ifndef EXAMPLEPROJECT_DEBUG_H
#define EXAMPLEPROJECT_DEBUG_H
// Quick prints for userInput.
inline void debugInput(int userInput) {
    std::cout << "USER INPUT READ: " << userInput << "\n";
}

// Quick prints for all possible moves.
inline void debugMoves(Problem::Direction *moves) {
    std::cout << "Possible Moves: "
              << "UP: " << moves[0] << ", "
              << "DOWN: " << moves[1] << ", "
              << "LEFT: " << moves[2] << ", "
              << "RIGHT: " << moves[3] << "\n";
}
#endif //EXAMPLEPROJECT_DEBUG_H
