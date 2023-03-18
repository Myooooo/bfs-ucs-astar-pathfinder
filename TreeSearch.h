#ifndef TREE_SEARCH_H
#define TREE_SEARCH_H

#include <vector>
#include "Map.h"
#include "Node.h"

class TreeSearch{

private:

    Map* map;                   // Pointer Map object that stores the relevant map information
    Node* root;                 // Pointer to the root Node of the tree structure
    int number_of_nodes;        // int variable that stores the number of nodes in the tree structure

public: 

    TreeSearch(char* path);                         // Constructor that takes the path of a text file containing the map information

    virtual std::vector<int*> search() = 0;         // Pure virtual function that executes search algorithms and returns the solution
    std::vector<Node*> expand(Node* node);          // Expands the input node and returns its children Nodes
    int calcStepCost(Node* oldState, int newState[2]);      // Calculates and returns the actual step cost by the different in elevation
    void deleteNodes(Node* root);                   // Deletes all nodes in the tree from a given root
    
    Map* getMap();                                  // Returns the pointer to the Map object
    Node* getRoot();                                // Returns the pointer to the root Node
    int getNumberOfNodes();                         // Returns the number of nodes

    ~TreeSearch();                                  // Destructor that deletes the map object and all nodes in the tree

};

#endif