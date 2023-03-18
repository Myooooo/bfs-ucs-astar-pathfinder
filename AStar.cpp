#include <cstddef>
#include <string.h>
#include "AStar.h"

using namespace std;

/*
 * Constructor that takes the path of a text file containing the map information
 * 
 * char* path: path of the input file containing map information
 */

AStar::AStar(char* path) : TreeSearch(path){
    queue.push_back(getRoot());
}

/*
 * Executes the A* search algorithms and returns the solution coordinations
 * 
 * return: coordinates of the solution as a vector of int arrays 
 */

vector<int*> AStar::search(){

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
            // calculate the heuristics for each child
            for(int i = 0; i < children.size(); i++){
                children[i] -> calcHeuristic(getMap() -> getGoal(), h_type);
            }
            // push all children to the end of the queue
            queue.insert(queue.end(), children.begin(), children.end());
        }
        
        // remove the expanded node in the queue according to its index
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
 * Calculates and returns the index of the node in queue with minimum cost and heuristic
 * 
 * return: index of the node in queue with minimum cost
 */

int AStar::minCostIndex(){

    float min = getTotalCost(0);
    int index = 0;

    // check if the queue has less than one node
    // otherwise iterate through the queue and find the node with minimum cost
    if(queue.size() <= 1){
        return 0;
    }else{
        for(int i = 1; i < queue.size(); i++){
            if(getTotalCost(i) < min){
                min = getTotalCost(i);
                index = i;
            }
        }
        return index;
    }
    
}

/*
 * Calculates and returns the total cost and heuristic of the node at the given index of the queue
 * 
 * int index: index of node in the queue
 * 
 * return: cost and heuristic of the node at index
 */

float AStar::getTotalCost(int index){
    return queue[index] -> getPathCost() + queue[index] -> getHeuristic();
}

/*
 * Sets the type of heuristic according to input, 0 for manhattan, 1 for euclidean
 * 
 * char* heuristic: the type of heuristic in words
 */

void AStar::setHType(char* heuristic){
    // compare input string
    h_type = strcmp(heuristic, "manhattan");
    // calculate root node heuristic
    getRoot() -> calcHeuristic(getMap() -> getGoal(), h_type);
}

/*
 * Destructor
 */

AStar::~AStar(){

}