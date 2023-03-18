#ifndef BFS_H
#define BFS_H

#include <deque>
#include <vector>
#include "TreeSearch.h"

class BFS : public TreeSearch{

private: 

    std::deque<Node*> queue;            // Priority queue for the sequence of node expansion

public:

    BFS(char* path);                    // Constructor that takes the path of a text file containing the map information

    std::vector<int*> search();         // Executes the Breadth First Search algorithms and returns the solution coordinations

    ~BFS();                             // Destructor

};

#endif