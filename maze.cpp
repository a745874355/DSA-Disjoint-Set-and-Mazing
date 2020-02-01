#include "wall.h"
#include "maze.h"
#include <cstdio>
#include <string>
#include <iostream>

Maze::Maze(int row, int col, Wall theWalls[], int numWalls){

	rows_=row;
	cols_=col;
	numCells_=row*col;
	cells_=new bool[row*col];
	walls_=new bool*[numCells_];
	for(int i=0;i<row*col;i++){
			cells_[i]=false;
	}
	for(int i=0;i<numCells_;i++){
		walls_[i]=new bool[numCells_];
		for(int j=0;j<numCells_;j++){
			walls_[i][j]=false;
		}
	}
	for(int i=0;i< numWalls;i++){
		walls_[theWalls[i].cell1()][theWalls[i].cell2()]=true;
		walls_[theWalls[i].cell2()][theWalls[i].cell1()]=true;
	}
}

//creates a maze from data stored in the file passed in
Maze::Maze(const char* mazeFileName){
	FILE* infile=fopen(mazeFileName,"r");
	fscanf(infile,"{ \"maxRow\": %d,",&rows_);
	fscanf(infile,"\"maxCol\": %d,",&cols_);
	fscanf(infile,"\"walls\": [");

	numCells_=rows_*cols_;
	cells_=new bool[rows_*cols_];
	walls_=new bool*[numCells_];
	for(int i=0;i<rows_*cols_;i++){
			cells_[i]=false;
	}
	for(int i=0;i<numCells_;i++){
		walls_[i]=new bool[numCells_];
		for(int j=0;j<numCells_;j++){
			walls_[i][j]=false;
		}
	}

	int w1;
	int w2;
	while(fscanf(infile,"[%d, %d], ",&w1,&w2)==2){
		walls_[w1][w2]=true;
		walls_[w2][w1]=true;
	}
}

bool Maze::isBeside(int cell1, int cell2) const{
	bool rc=false;
	//ensure that both cells are valid cells first
	if((cell1 >=0 && cell1 < numCells_) && 
		(cell2 >=0 && cell2 <numCells_)){

		if(getRow(cell1) == getRow(cell2)){
			//if same row then two cells have numbers beside each other so 
			//their numbers must be one apart
			if(abs(cell1-cell2)==1){
				rc=true;
			}
		}	
		else if(getCol(cell1)==getCol(cell2)){
			if(abs(cell1-cell2)==cols_){
				rc=true;
			}
		}
	}
	return rc;
}

// function returns true if both of the following
// conditions are met:
//
// 1. fromCell is beside toCell (immeditately to 
//    up/down/left/right of each other)
// 2. there is no wall between fromCell and toCell
bool Maze::canGo(int fromCell,int toCell) const{
	bool rc=false;
	if(isBeside(fromCell,toCell) && !walls_[fromCell][toCell])
		rc=true;
	return rc;
}

//returns the cell number of the cell in position row,col (top left is 0,0)
int Maze::getCell(int row,int col) const{
	return row*cols_ + col;
}

//marks a cell as being visited
void Maze::mark(int cellNumber){
	cells_[cellNumber]=true;
}

//returns the row number of the cell with cellNumber
int Maze::getRow(int cellNumber) const{
	return cellNumber/cols_;
}
//returns the row number of the cell with cellNumber
int Maze::getCol(int cellNumber) const{
	return cellNumber%cols_;
}

//unmarks a cell as being visited
void Maze::unMark(int cellNumber){
	cells_[cellNumber]=false;
}

//returns true if the cell Number is Marked as visited.
bool Maze::isMarked(int cellNumber){
	return cells_[cellNumber];
}


Maze::~Maze(){
	for(int i=0;i<numCells_;i++){
		delete [] walls_[i];
	}
	delete [] walls_;
	delete [] cells_;
}
