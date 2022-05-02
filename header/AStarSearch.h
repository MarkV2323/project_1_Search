#ifndef EXAMPLEPROJECT_ASTARSEARCH_H
#define EXAMPLEPROJECT_ASTARSEARCH_H
#include <queue>
#include <set>

#include "../header/Node.h"

class AStarSearch {
public:
    AStarSearch();

    static Node* search1(Problem* problem);
    static Node* search2(Problem* problem);

    virtual ~AStarSearch();
};
#endif //EXAMPLEPROJECT_ASTARSEARCH_H
