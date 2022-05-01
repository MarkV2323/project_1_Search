#include <queue>
#include <set>

#include "../header/Node.h"

class uniformSearch {
private:
    int nodesCreated;
public:
    uniformSearch() {
        nodesCreated = 0;
    }

    static Node* search(Problem* problem) {
        // init return Node
        Node* node = new Node(problem);

        // init frontier with node as the only element.
        std::priority_queue<Node*> frontier;
        frontier.push(node);

        // init empty set.
        std::set<Node*> explored;
        
        return node;
    }
};
