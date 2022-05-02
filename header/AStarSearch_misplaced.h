#ifndef EXAMPLEPROJECT_ASTARSEARCH_MISPLACED_H
#define EXAMPLEPROJECT_ASTARSEARCH_MISPLACED_H
#include <queue>
#include <set>

#include "../header/Node.h"

class AStarSearch_misplaced {
public:
    AStarSearch_misplaced();
    static Node* search(Problem* problem);
    virtual ~AStarSearch_misplaced();
};
#endif //EXAMPLEPROJECT_ASTARSEARCH_MISPLACED_H
