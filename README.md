# bfs-ucs-astar-pathfinder
A pathfinder for 2D grids that implements the BFS, UCS and A* search algorithms

## Build
```
make all
```

For A* Search, two heuristics have been implemented:
- Euclidean distance between current position and end position.
- Manhattan distance between current position and end position.

## Sample input map

```
1 1 1 1 1 1 4 7 8 X
1 1 1 1 1 1 1 5 8 8
1 1 1 1 1 1 1 4 6 7
1 1 1 1 1 X 1 1 3 6
1 1 1 1 1 X 1 1 1 1
1 1 1 1 1 1 1 1 1 1
6 1 1 1 1 X 1 1 1 1
7 7 1 X X X 1 1 1 1
8 8 1 1 1 1 1 1 1 1
X 8 7 1 1 1 1 1 1 1
```

Given a start position and an end position on the map, our aim is to find a path from the start position to the end position. 
The character ‘X’ denotes an obstacle that cannot be traversed by a path, while the digits represent the elevation at the respective positions.
Any position is indicated by the coordinates (i, j), where i is the row number (ordered top to bottom) and j is the column number (ordered left to right). For example, the top left position is (1, 1), the bottom right is (10, 10), while the position with elevation ‘3’ is (4, 9). Given start position (1, 1) and end position (10, 10), a possible path is: 
```
* * * 1 1 1 4 7 8 X
1 1 * 1 1 1 1 5 8 8
1 1 * * * * * * * 7
1 1 1 1 1 X 1 1 * 6
1 1 1 1 1 X 1 * * 1
1 1 1 1 1 1 1 * 1 1
6 1 1 1 1 X 1 * * *
7 7 1 X X X 1 1 1 *
8 8 1 1 1 1 1 1 1 *
X 8 7 1 1 1 1 1 * *
```
Note that we use 4-connectedness for paths, which means any two points on the path are only connected if they are vertically or horizontally (but not diagonally!) adjacent.

## Problem formulation
- States: Any obstacle-free position (i,j) on the map.
- Initial state: A position (i0,j0) given by the user.
- Actions: Since we consider 4-connectedness, only four actions are available: Up, down, left and right (your program must expand each node in this order). Available actions for positions adjacent to the map boundary or obstacles are reduced accordingly.
- Transition model: Moving left moves the current position to the left, etc.
- Goal test: Check if the current state is the end position (i∗, j∗) given by the user.
- Path cost: Given a map M and a path P = {(i0,j0),(i1,j1),...,(iN,jN)}, the cost of the path is calculated as
```
g(P) = SUM(c(ik−1,jk−1,ik,jk,M))
```
where
```
c(a,b,c,d,M) = (1+M(c,d)−M(a,b) if M(c,d)−M(a,b)>0 
            = 1 otherwise
```
and M(a,b) is the elevation at position (a,b). In words, the cost of a path is the sum of the costs between two adjacent points of the path, and the cost between adjacent points is 1 plus the difference between the elevation of the two points if we climb “uphill”, or simply 1 if we stay “level” or slide “downhill”.

