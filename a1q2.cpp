#include "wall.h"
#include "disjointset.h"
#include "permutation.h"
void find_adjacent_rooms( int room[2], int wall, int n ) {
    // Determine which row and column
	if(wall > 0) {
		
		int row = (wall - 1) / (2 * n - 1);  //1
		int column = (wall - 1) % (2 * n - 1);   //3

		// Determine which rooms they connect
		if (column < n - 1) {    //n-1 = 2
			// A vertical wall
			room[0] = n * row + column;
			room[1] = n * row + column + 1;
		}
		else {
			// A horizontal wall
			column += 1 - n;                 //c= 3 + 1 - 3 = 1

			room[0] = n * row + column;  //3*1+1=4
			room[1] = n * (row + 1) + column;  //3*2+1= 7
		}
	}  
}

int generateMaze(int row, int col, Wall walls[]) {
	//get cells number, walls number
	int cells_num = row * col;
	int disjoint_sets_num = 0;
	int walls_num = 2 * row * col - row - col;  
	int rc = 0;
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
		while (disjoint_sets_num > 1) {
			 
				int wall = untested_walls.next();
				//test
				std::cout << wall << ' ';
				int room[2];
				find_adjacent_rooms(room, wall, col);
				walls[wall].set(room[0], room[1]);
				// If the two rooms are not connected,
				//   remove the wall between them and
				//   take the union of the two sets.
				if (rooms.findSet(walls[wall].cell1()) != rooms.findSet(walls[wall].cell2())) {
					// isWall[wall] = false;
					rooms.unionSets(room[0], room[1]);
					walls[wall].set(-1, -1);
					disjoint_sets_num--;
					walls_num--;
				}
				 
		 };
		//test
		std::cout << std::endl;
		rc = walls_num;
	}
	return rc;
       
}
