#include <iostream>
#include <vector>
#include <string.h>
#include "Map.h"
#include "BFS.h"
#include "UCS.h"
#include "AStar.h"

using namespace std;


int main(int argc, char** argv){

    // copy input arguments
    char* path = argv[1];
    char* algorithm = argv[2];
    char* heuristic = argv[3];

    // create objects
    Map map(path);
    BFS bfs(path);
    UCS ucs(path);
    AStar astar(path);

    // create solution vector
    vector<int*> solution;

    // check for input algorithm and execute search
    if(!strcmp(algorithm, "bfs")){
        solution = bfs.search();
    }else if(!strcmp(algorithm, "ucs")){
        solution = ucs.search();
    }else{
        // set heuristic type
        astar.setHType(heuristic);
        solution = astar.search();
    }

    // if there's no solution print null
    if(solution.size() == 0){
        cout << "null" << endl;
    // otherwise print the map with marked solutions
    }else{
        map.drawSolution(solution);
        map.drawMap();
    }
    
    return 0;
}