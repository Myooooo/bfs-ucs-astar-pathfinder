#ifndef MAP_H
#define MAP_H

#include <vector>

class Map{

private:

	char** map;				// char 2d-array that stores the map
	int rows;				// int variable that stores the number of rows of the map
	int columns;			// int variable that stores the number of columns of the map
	int initialState[2];	// int array that stores the coordinate of the initial state in the map
	int goal[2];			// int array that stores the coordinate of the goal state in the map
	bool actions[4];		// bool array that stores the validity of moving into up, down, left, right directions

public:

	Map(char* path);					// Constructor that takes the path of a text file containing the map information

	void initMap(char* path); 			// Initiates the map from file at the input path
	void drawMap();						// Prints the map into terminal
	void deleteMap();					// Deletes the map from the heap	
	void drawSolution(std::vector<int*> states);	// Marks the solution coordinates as * on the map

	void markState(int i, int j);		// Marks * at map(i,j)
	bool isValid(int i, int j);			// Checks if the map(i,j) is obstacle or visited before
	int getCost(int i, int j);			// Returns the elevation of map(i,j)
	bool* validActions(int i, int j);	// Returns the array of valid actions at map(i,j)
	bool isGoal(int state[2]);			// Checks if the input state is the goal
	
	int getRows();						// Returns the number of rows in the map
	int getColumns();					// Returns the number of columns in the map
	int* getInitialState();				// Returns the coordinate of the initial state
	int* getGoal();						// Returns the coordinate of the goal state

	~Map();								// Destructor that deletes the map from heap

};

#endif