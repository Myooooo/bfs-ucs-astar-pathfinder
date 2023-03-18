#ifndef UCS_H
#define UCS_H

#include <deque>
#include <vector>
#include "TreeSearch.h"

class UCS : public TreeSearch{

private:

    std::deque<Node*> queue;            // Priority queue for the sequence of node expansion

public: 

    UCS(char* path);                    // Constructor that takes the path of a text file containing the map information

    std::vector<int*> search();         // Executes the Uniform Cost Search algorithms and returns the solution coordinations
    int minCostIndex();                 // Calculates and returns the index of the node in queue with minimum cost

    ~UCS();                             // Destructor

};

#endif