#include <cstddef>
#include <cstdlib>
#include <cmath>
#include "Node.h"

using namespace std;

/*
 * Constructor used for creating the root node
 * 
 * int state[2]: state of the node
 * int elevation: elevation at the given state
 */

Node::Node(int state[2], int elevation){

    // copy the input variables
    this -> state[0] = state[0];
    this -> state[1] = state[1];
    this -> elevation = elevation;

    // initialize the variables to 0
    depth = 0;
    pathCost = 0;
    parent = NULL;

}

/*
 * Constructor used for creating all the other nodes
 * 
 * int state[2]: state of the node
 * int elevation: elevation at the given state
 * Node* parent: pointer to the parent node
 * int cost: step cost from its parent to the node
 */

Node::Node(int state[2], int elevation, Node* parent, int cost){

    // copy the input variables
    this -> state[0] = state[0];
    this -> state[1] = state[1];
    this -> elevation = elevation;

    // set variables according to its parent and inputs
    depth = parent -> getDepth() + 1;
    pathCost = parent -> getPathCost() + cost;
    this -> parent = parent;

}

/*
 * Sets the child nodes of the node
 * 
 * vector<Node*> children: vector of pointers to the child nodes
 */

void Node::setChildren(vector<Node*> children){
    this -> children = children;
}

/*
 * Calculates and sets the heuristic value of the node
 * 
 * int* goal: coordinates of the goal state
 * int type: type of heuristic, 0 for manhattan, 1 for euclidean
 */

void Node::calcHeuristic(int* goal, int type){

    // calculate heuristic as manhattan when type = 0
    if(!type){
        heuristic = abs(goal[0] - state[0]) + abs(goal[1] - state[1]);
    // calculate heuristic as euclidean when type = 1
    }else{
        heuristic = sqrt(pow(goal[0] - state[0], 2) + pow(goal[1] - state[1], 2));
    }

}

/*
 * Returns the coordinates of the node
 * 
 * return: coordinates of the node
 */

int* Node::getState(){
    return state;
}

/*
 * Returns the depth of the node
 * 
 * return: depth of the node
 */

int Node::getDepth(){
    return depth;
}

/*
 * Returns the path cost of the node
 * 
 * return: path cost of the node
 */

int Node::getPathCost(){
    return pathCost;
}

/*
 * Returns the elevation of the node
 * 
 * return: elevation of the node
 */

int Node::getElevation(){
    return elevation;
}

/*
 * Returns the heuristic of the node
 * 
 * return: heuristic of the node
 */

float Node::getHeuristic(){
    return heuristic;
}

/*
 * Returns the parent node
 * 
 * return: pointer to the parent node
 */

Node* Node::getParent(){
    return parent;
}

/*
 * Returns the child nodes
 * 
 * return: vector of pointers to the child nodes
 */

vector<Node*> Node::getChildren(){
    return children;
}

/*
 * Destructor
 */

Node::~Node(){

}