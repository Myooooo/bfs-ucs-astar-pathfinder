#include "TreeSearch.h"

using namespace std;

/*
 * Constructor that takes the path of a text file containing the map information
 * 
 * char* path: path of the input file containing map information
 */

TreeSearch::TreeSearch(char* path){

    // create a map object using file at given path
    map = new Map(path);

    // read initial state from map and create a root node
    int* state = getMap() -> getInitialState();
    root = new Node(state, map -> getCost(state[0], state[1]));

    // initialize the number of nodes to 1
    number_of_nodes = 1;

}

/*
 * Expands the input node and returns its children Nodes
 * 
 * Node* node: pointer to the node that is to be expanded
 * 
 * return: child nodes of the input node as a vector of node pointers 
 */

vector<Node*> TreeSearch::expand(Node* node){

    // declare required variables
    int* state;
    bool* actions;
    int stepCost;
    vector<Node*> children;
    int newState[2];

    // read the state from input node and get its valid actions
    // up, down, left, right
    state = node -> getState();
    actions = map -> validActions(state[0], state[1]);

    // iterate through valid actions
    for(int i = 0; i < 4; i++){

        if(actions[i] == true){

            // set the new state coordinates according to action
            switch(i){
                case 0:
                    newState[0] = state[0] - 1;
                    newState[1] = state[1];
                    break;
                case 1:
                    newState[0] = state[0] + 1;
                    newState[1] = state[1];
                    break;
                case 2:
                    newState[0] = state[0];
                    newState[1] = state[1] - 1;
                    break;
                case 3:
                    newState[0] = state[0];
                    newState[1] = state[1] + 1;
                    break;
                default:
                    break;
            }
            
            // calculate the actual step cost
            stepCost = calcStepCost(node, newState);

            // create a new node on the heap and store its address into the vector
            children.push_back(new Node(newState, map -> getCost(newState[0], newState[1]), node, stepCost));

        }
    }

    // mark the node and its children to *
    map -> markState(state[0], state[1]);
    for(int i = 0; i < children.size(); i++){
        state = children[i] -> getState();
        map -> markState(state[0], state[1]);
    }

    // set child nodes and record total number of nodes in memory
    node -> setChildren(children);
    number_of_nodes += children.size();

    return children;

}

/*
 * Calculates and returns the actual step cost by the different in elevation
 * 
 * Node* oldState: pointer to the old state node
 * int newState[2]: coordinates of the new state
 * 
 * return: the actual step cost by difference in elevation
 */

int TreeSearch::calcStepCost(Node* oldState, int newState[2]){

    // get the elevation values for old state and new state
    int oldElevation = oldState -> getElevation();
    int newElevation = map -> getCost(newState[0], newState[1]);

    // calculate and return the actual step cost
    if(newElevation > oldElevation){
        return 1 + newElevation - oldElevation;
    }else{
        return 1;
    }

}

/*
 * Deletes all nodes in the tree from a given root
 * 
 * Node* root: pointer to the root node of the tree structure
 */

void TreeSearch::deleteNodes(Node* root){

    // store the child nodes of the root node into a vector
    vector<Node*> children = root -> getChildren();

    // call this function recursively on the child nodes
    for(int i = 0; i < children.size(); i++){
        deleteNodes(children[i]);
    }

    // decrement the number of nodes in the tree
    number_of_nodes --;
   
    // delete the root node
    delete root;
    
}

/*
 * Returns the pointer to the Map object
 * 
 * return: pointer to the Map object
 */

Map* TreeSearch::getMap(){
    return map;
}

/*
 * Returns the pointer to the root Node
 * 
 * return: pointer to the root Node
 */

Node* TreeSearch::getRoot(){
    return root;
}

/*
 * Returns the number of nodes
 * 
 * return: number of nodes in the tree structure
 */

int TreeSearch::getNumberOfNodes(){
    return number_of_nodes;
}

/*
 * Destructor that deletes the map object and all nodes in the tree
 */

TreeSearch::~TreeSearch(){
    delete map;
    deleteNodes(root);
}