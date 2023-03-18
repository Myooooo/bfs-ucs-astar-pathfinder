all: 
	pathfinder

pathfinder: 
	g++ *.cpp -std=c++11 -o pathfinder.bin

clean: 
	rm pathfinder.bin