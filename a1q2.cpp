#include "wall.h"
#include "disjointset.h"
#include "permutation.h"
//according wall number and column number
//determine the rooms and store the adjacent rooms number to room[0] room[1]
void find_adjacent_rooms( int room[2], int wall, int col ) {
    // Determine which row and column
    // row num range [0, row-1]
    // col num range [0, col-1]
	if(wall > 0) {
		
		int row = (wall - 1) / (2 * col - 1);
		int column = (wall - 1) % (2 * col - 1);

		// Determine which rooms they connect
		if (column < col - 1) {
			// A vertical wall
			room[0] = col * row + column;
			room[1] = col * row + column + 1;
		}
		else {
			// A horizontal wall
                        // adjust column number
			column += 1 - col;
			 
			room[0] = col * row + column;
			room[1] = col * (row + 1) + column;
		}
	}  
}

// according to the row and col number, generate a maze and store the walls of the maze to walls array.function return the number of the remaining walls.
int generateMaze(int row, int col, Wall walls[]) {
	//get cells number, walls number
	int cells_num = row * col;
	int walls_num = 2 * row * col - row - col;
        int disjoint_sets_num = 0;
	int rc = 0;
	int index = 0;
    
        // only when both row and col > 1, maze exist
	if (row > 1 && col > 1 ) {

		//makeset for each cell
		DisjointSet rooms(cells_num);
		for (int i = 0; i < cells_num && rooms.makeSet(i); i++) {
			disjoint_sets_num++;
		}
		//create Permutation obj to store untested walls which could make sure each wall only can be selected randomly without duplicate
		Permutation untested_walls(walls_num);
 
		//randamly find two adjacent rooms, if two rooms are not in same disjoint set, union them
                //otherwise, store the wall between them to the next index of Wall array.
		while (disjoint_sets_num > 1 ){
			//through wall, get two adjacent rooms number, store in room[0], room[1]
			int wall = untested_walls.next();
			int room[2];
			find_adjacent_rooms(room, wall, col);
		 
			// If the two rooms are not connected, take the union of the two room.
			//otherwise, store the wall to the next index of Wall array
			if (rooms.findSet(room[0]) != rooms.findSet(room[1])) {				 
				rooms.unionSets(room[0], room[1]);
				disjoint_sets_num--;
				walls_num--;
			}
                        
			else {
                		walls[index].set(room[0], room[1]);
                		//prevent segmentation fault
                		if(index < walls_num) index++;
			}

		};
		//check all the rest walls, store the adjacent rooms numbers at the end of walls array
		while (index < walls_num) {
			int wall = untested_walls.next();
			int room[2];
			find_adjacent_rooms(room, wall, col);
			walls[index++].set(room[0], room[1]);

		}
		rc = walls_num;
	}

	return rc;

}
 
