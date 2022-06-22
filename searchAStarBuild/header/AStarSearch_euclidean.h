#ifndef EXAMPLEPROJECT_ASTARSEARCH_EUCLIDEAN_H
#define EXAMPLEPROJECT_ASTARSEARCH_EUCLIDEAN_H
#include <queue>
#include <set>

#include "../header/Node.h"
class AStarSearch_euclidean {
public:
    AStarSearch_euclidean();
    static Node* search(Problem* problem);
    virtual ~AStarSearch_euclidean();
};
#endif //EXAMPLEPROJECT_ASTARSEARCH_EUCLIDEAN_H
