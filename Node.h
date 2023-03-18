#ifndef NODE_H
#define NODE_H

#include <vector>

class Node{

private: 

    int state[2];                       // int array that stores the coordinates of the node
    int depth;                          // int variable that stores the depth of the node
    int pathCost;                       // int variable that stores the path cost of the node
    int elevation;                      // int variable that stores the elevation of the node
    float heuristic;                    // float variable that stores the heuristic value of the node
    Node* parent;                       // Pointer to the parent node
    std::vector<Node*> children;        // vector of pointer to the child nodes

public:

    Node(int state[2], int elevation);                          // Constructor used for creating the root node
    Node(int state[2], int elevation, Node* parent, int cost);  // Constructor used for creating all the other nodes

    void setChildren(std::vector<Node*> input_children);        // Sets the child nodes of the node
    void calcHeuristic(int* goal, int type);                    // Calculates and sets the heuristic value of the node

    int* getState();                                            // Returns the coordinates of the node
    int getDepth();                                             // Returns the depth of the node
    int getPathCost();                                          // Returns the path cost of the node
    int getElevation();                                         // Returns the elevation of the node
    float getHeuristic();                                       // Returns the heuristic of the node
    Node* getParent();                                          // Returns the parent node
    std::vector<Node*> getChildren();                           // Returns the child nodes

    ~Node();                                                    // Destructor

};

#endif