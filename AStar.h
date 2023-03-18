#ifndef ASTAR_H
#define ASTAR_H

#include <deque>
#include <vector>
#include "TreeSearch.h"

class AStar : public TreeSearch{

private:

    int h_type;                         // Stores the type of heuristic, 0 for manhattan, 1 for euclidean
    std::deque<Node*> queue;            // Priority queue for the sequence of node expansion

public: 

    AStar(char* path);                  // Constructor that takes the path of a text file containing the map information

    std::vector<int*> search();         // Executes the A* search algorithms and returns the solution coordinations
    int minCostIndex();                 // Calculates and returns the index of the node in queue with minimum cost and heuristic
    float getTotalCost(int index);      // Calculates and returns the total cost and heuristic of the node at the given index of the queue
    void setHType(char* heuristic);     // Sets the type of heuristic according to input, 0 for manhattan, 1 for euclidean
    
    ~AStar();                           // Destructor

};

#endif