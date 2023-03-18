#include <cstddef>
#include "UCS.h"

using namespace std;

/*
 * Constructor that takes the path of a text file containing the map information
 * 
 * char* path: path of the input file containing map information
 */

UCS::UCS(char* path) : TreeSearch(path){
    queue.push_back(getRoot());
}

/*
 * Executes the Uniform Cost Search algorithms and returns the solution coordinations
 * 
 * return: coordinates of the solution as a vector of int arrays 
 */

vector<int*> UCS::search(){

    // declare variables
    Node* goal;
    vector<Node*> children;
    vector<int*> solution;

    // flag that marks if theres a solution
    bool flag = true;

    // set the index to 0 and get the state of the first item in queue
    int index = 0;
    int* state = queue[index] -> getState();

    // iterate through the map until reaching the goal state
    while(!(getMap() -> isGoal(state))){

        // expand the node and store its child nodes
        children = expand(queue[index]);

        // add child nodes into the queue
        if(children.size() > 0){
            queue.insert(queue.end(), children.begin(), children.end());
        }
        
        // remove the expanded node in queue according to its index
        queue.erase(queue.begin() + index);

        // if the queue is not empty expand the next node with minimum cost
        // otherwise mark the flag as false
        if(queue.size() != 0){
            index = minCostIndex();
            state = queue[index] -> getState();
        }else{
            flag = false;
            break;
        }

    }

    // add solution coordinates to the vector if there is a solution
    if(flag){
        goal = queue[index];
        while(goal -> getParent() != NULL){
            solution.push_back(goal -> getState());
            goal = goal -> getParent();
        }
        solution.push_back(goal -> getState());
    }

    return solution;
}

/*
 * Calculates and returns the index of the node in queue with minimum cost
 * 
 * return: index of the node in queue with minimum cost
 */

int UCS::minCostIndex(){

    int min = queue[0] -> getPathCost();
    int index = 0;

    // check if the queue has less than one node
    // otherwise iterate through the queue and find the node with minimum cost
    if(queue.size() <= 1){
        return 0;
    }else{
        for(int i = 1; i < queue.size(); i++){
            if((queue[i] -> getPathCost()) < min){
                min = queue[i] -> getPathCost();
                index = i;
            }
        }
        return index;
    }
    
}

/*
 * Destructor
 */

UCS::~UCS(){
    
}