#ifndef MAZE_H
#define MAZE_H

#include "wall.h"
#include <string>

class Maze{
   bool* cells_;
   bool** walls_;
   int rows_;
   int cols_;
   int numCells_;
   bool isBeside(int cell1, int cell2) const;
public:
	//creates a maze
	Maze(int row, int col, Wall theWalls[],int numWAlls);

    //creates a maze from data stored in the file passed in
	Maze(const char* mazeFileName);

	//returns number of rows in the maze
	int numRows() const {return rows_;}

	//returns number of cols in the maze
	int numCols() const {return cols_;}
	// function returns true if both of the following
	// conditions are met:
	//
	// 1. fromCell is beside toCell (immeditately to 
	//    up/down/left/right of each other)
	// 2. there is no wall between fromCell and toCell
	bool canGo(int fromCell,int toCell) const;

	//returns the cell number of the cell in position row,col (top left is 0,0)
	int getCell(int row,int col) const;

	//returns the row number of the cell with cellNumber, 0 is top row
	int getRow(int cellNumber) const;


	//returns the col number of the cell with cellNumber, 0 is leftmost col
	int getCol(int cellNumber) const;

	//marks a cell as being visited
	void mark(int cellNumber);

	//unmarks a cell as being visited
	void unMark(int cellNumber);

	//returns true if the cell Number is Marked as visited.
	bool isMarked(int cellNumber);


	~Maze();
};

#endif