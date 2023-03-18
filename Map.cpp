#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Map.h"

using namespace std;

/*
 * Constructor that takes the path of a text file containing the map information
 * 
 * char* path: path of the input file containing map information
 */

Map::Map(char* path){
	initMap(path);
}

/*
 * Initiates the map from file at the input path
 * 
 * char* path: path of the input file containing map information
 */

void Map::initMap(char* path){

	ifstream readFile(path);
	stringstream ss;
	int counter = 0;

	// iterate through each line of the file
	for(string line; getline(readFile, line);){

		// initiate string stream
		ss.clear();
		ss.str(line);

		// read the first line as rows and colums
		if(counter == 0){

			ss >> rows >> columns;

			// create the map on the heap according to rows and columns
			map = new char*[rows];
			for(int i = 0; i < rows; i++){
        		map[i] = new char[columns];
    		}

		// read the second line as initiate state
		}else if(counter == 1){

			ss >> initialState[0] >> initialState[1];

			// convert to C++ coordinates
			initialState[0] -= 1;
			initialState[1] -= 1;

		// read the third line as goal state
		}else if(counter == 2){

			ss >> goal[0] >> goal[1];

			// convert to C++ coordinates
			goal[0] -= 1;
			goal[1] -= 1;

		// read the rest of the file as the map
		}else{

			// copy the values into map
			for(int j = 0; j < columns; j++){
				ss >> map[counter - 3][j];
			}

		}

		// increment the counter for each iteration
		counter ++;
	}
	
	readFile.close();

}

/*
 * Prints the map into terminal
 */

void Map::drawMap(){

	for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

}

/*
 * Deletes the map from the heap	
 */

void Map::deleteMap(){

	for(int i = 0; i < rows; i++){
        delete[] map[i];
    }
    delete[] map;

}

/*
 * Marks the solution coordinates as * on the map
 * 
 * vector<int*> states: a vector of int arrays that stores the coordinates of the solution
 */

void Map::drawSolution(vector<int*> states){

	int* state;

	// iterate through the vector and mark the coordinates in the map
	for(int i = 0; i < states.size(); i++){
		state = states.at(i);
		markState(state[0], state[1]);
	}

}

/*
 * Marks * at map(i,j)
 * 
 * int i: x coordinate in the map
 * int j: y coordinate in the map
 */

void Map::markState(int i, int j){

	map[i][j] = '*';

}

/*
 * Checks if the map(i,j) is obstacle or visited before
 * 
 * int i: x coordinate in the map
 * int j: y coordinate in the map
 * 
 * return: true when map(i,j) is valid to go, false when it is an obstable marked as expanded
 */

bool Map::isValid(int i, int j){

	// check for obstacles or marks
	if(map[i][j] == '*' || map[i][j] == 'X'){
		return false;
	}else{
		return true;
	}

}

/*
 * Returns the elevation of map(i,j)
 * 
 * int i: x coordinate in the map
 * int j: y coordinate in the map
 * 
 * return: elevation of map(i,j)
 */

int Map::getCost(int i, int j){

	// convert from char to int
	return map[i][j] - '0';

}

/*
 * Returns the array of valid actions at map(i,j)
 * 
 * int i: x coordinate in the map
 * int j: y coordinate in the map
 * 
 * return: array of bools containing validity of going up, down, left, right
 */

bool* Map::validActions(int i, int j){

	// up, down, left, right
	// initiate all actions to true
	for(int action = 0; action < 4; action++){
		actions[action] = true;
	}

	// detect the top and bottom borders of the map
	if(i == 0){
		actions[0] = false;
	}else if(i == rows - 1){
		actions[1] = false;
	}

	// detect the left and right borders of the map
	if(j == 0){
		actions[2] = false;
	}else if(j == columns - 1){
		actions[3] = false;
	}

	// detect obstacles and marked states
	for(int action = 0; action < 4; action ++){
		if(actions[action] == true){
			switch(action){
				case 0:
					actions[action] = isValid(i - 1, j);
					break;
				case 1:
					actions[action] = isValid(i + 1, j);
					break;
				case 2:
					actions[action] = isValid(i, j - 1);
					break;
				case 3:
					actions[action] = isValid(i, j + 1);
					break;
				default:
					break;
			}
		}
	}

	return actions;

}

/*
 * Checks if the input state is the goal
 * 
 * int state[2]: x and y coordinates in the map
 * 
 * return: true when input matches the goal, false otherwise
 */

bool Map::isGoal(int state[2]){

	// compare input with goal
	if(state[0] == goal[0] && state[1] == goal[1]){
		return true;
	}else{
		return false;
	}

}

/*
 * Returns the number of rows in the map
 * 
 * return: number of rows in the map
 */

int Map::getRows(){
	return rows;
}

/*
 * Returns the number of columns in the map
 * 
 * return: number of columns in the map
 */

int Map::getColumns(){
	return columns;
}

/*
 * Returns the coordinate of the initial state
 * 
 * return: x and y coordinates of the initial state in the map
 */

int* Map::getInitialState(){
	return initialState;
}

/*
 * Returns the coordinate of the goal state
 * 
 * return: x and y coordinates of the goal state in the map
 */

int* Map::getGoal(){
	return goal;
}

/*
 * Destructor that deletes the map from heap
 */

Map::~Map(){
	deleteMap();
}