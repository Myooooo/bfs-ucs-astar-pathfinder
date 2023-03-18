#include <cstddef>
#include "BFS.h"

using namespace std;

/*
 * Constructor that takes the path of a text file containing the map information
 * 
 * char* path: path of the input file containing map information
 */

BFS::BFS(char* path) : TreeSearch(path){
    queue.push_back(getRoot());
}

/*
 * Executes the Breadth First Search algorithms and returns the solution coordinations
 * 
 * return: coordinates of the solution as a vector of int arrays 
 */

vector<int*> BFS::search(){

    // declare variables
    Node* goal;
    vector<Node*> children;
    vector<int*> solution;

    // flag that marks if theres a solution
    bool flag = true;

    // get the state of the first item in queue
    int* state = queue[0] -> getState();

    // iterate through the map until reaching the goal state
    while(!(getMap() -> isGoal(state))){

        // expand the node and store its child nodes
        children = expand(queue[0]);

        // add child nodes into the queue
        if(children.size() > 0){
            queue.insert(queue.end(), children.begin(), children.end());
        }

        // pop the expanded node from the queue 
        queue.pop_front();

        // if the queue is not empty expand the next node in the queue
        // otherwise mark the flag as false
        if(queue.size() != 0){
            state = queue[0] -> getState();
        }else{
            flag = false;
            break;
        }

    }

    // add solution coordinates to the vector if there is a solution
    if(flag){
        goal = queue[0];
        while(goal -> getParent() != NULL){
            solution.push_back(goal -> getState());
            goal = goal -> getParent();
        }
        solution.push_back(goal -> getState());
    }

    return solution;
}

/*
 * Destructor
 */

BFS::~BFS(){

}