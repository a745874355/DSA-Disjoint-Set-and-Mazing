#include "wall.h"
#include "disjointset.h"
#include "permutation.h"
//store the adjacent rooms number to room[0] room[1], 
void find_adjacent_rooms( int room[2], int wall, int n ) {
    // Determine which row and column
	if(wall > 0) {
		
		int row = (wall - 1) / (2 * n - 1);    //range[0, row-1]
		int column = (wall - 1) % (2 * n - 1);  //range[0, col-1]

		// Determine which rooms they connect
		if (column < n - 1) {   
			// A vertical wall
			room[0] = n * row + column;
			room[1] = n * row + column + 1;
		}
		else {
			// A horizontal wall
			column += 1 - n;            
			 
			room[0] = n * row + column;   
			room[1] = n * (row + 1) + column;   
		}
	}  
}

int generateMaze(int row, int col, Wall walls[]) {
	//get cells number, walls number
	int cells_num = row * col;
	int disjoint_sets_num = 0;
	int walls_num = 2 * row * col - row - col; //2*4*4-8=24
	int rc = 0;
	int index = 0;
	if (row == 1) {
		 
		for (int i = 0; i < walls_num; i++) {
			walls[i].set(-1, -1);
		}
	}
	else if (col == 1) {
		for (int i = 0; i < walls_num; i++) {
			walls[i].set(-1, -1);
		}
	}
	else {

		//makeset for each cell
		DisjointSet rooms(cells_num);
		for (int i = 0; i < cells_num && rooms.makeSet(i); i++) {
			disjoint_sets_num++;
		}
		//create Permutation obj to store room
		Permutation untested_walls(walls_num);
 
		//randamly find two adjacent rooms 
		while (disjoint_sets_num > 1 ){
			
			int wall = untested_walls.next();
 
			int room[2];
			find_adjacent_rooms(room, wall, col);
		 
			// If the two rooms are not connected,
			//   remove the wall between them and
			//   take the union of the two sets.
			if (rooms.findSet(room[0]) != rooms.findSet(room[1])) {				 
				rooms.unionSets(room[0], room[1]);
				disjoint_sets_num--;
				walls_num--;
							 
			}
			else {				 		 
				walls[index++].set(room[0], room[1]);
			}
		};
		//check the all the rest walls, store the adjacent rooms numbers at the end of walls array
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
 
