#ifndef EXAMPLEPROJECT_UNIFORMSEARCH_H
#define EXAMPLEPROJECT_UNIFORMSEARCH_H
#include <queue>
#include <set>

#include "../header/Node.h"

class UniformSearch {
public:
    UniformSearch();
    static Node* search(Problem* problem);

};

#endif //EXAMPLEPROJECT_UNIFORMSEARCH_H
