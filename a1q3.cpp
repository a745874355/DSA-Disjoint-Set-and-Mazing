#include "wall.h"
#include "maze.h"
#include <iostream>



//The function search the path from endCell to startCell of a Maze recursively and returns the number of cells it went through for a success path and path[] will be modified.
//If no path found, the program returns 0
int runMaze(Maze& theMaze, int path[], int startCell, int endCell){
    #ifdef _DEBUG
    std::cout << startCell << "-" << endCell <<std::endl;
    #endif
    int rc = 0;
	auto x = theMaze.getCol(endCell);
    auto y = theMaze.getRow(endCell);
    auto xEdge = theMaze.numCols()-1;
    auto yEdge = theMaze.numRows() -1;
    theMaze.mark(endCell); //mark current cell.
    if (startCell == endCell)
    {
        path[0] = startCell; //we reached destination, start returns and save the path.
        return 1;
    }else{
        // cell identifies, X is current:
        //   0 
        // 1 X 2
        //   3  
        int cells[4]{0};
        if (x == 0) //left xEdge
        {
            cells[1] = -1;
        }
        if (x == xEdge) //right xEdge
        {
            cells[2] = -1;
        }
        if (y == 0) //top yEdge
        {
            cells[0] = -1;
        }
        if (y == yEdge) //bottom yEdge
        {
            cells[3] = -1;
        }
        //so far, the value in cells[n] which is not -1 means there is a cell at cells[n];
        for (size_t i = 0; i < 4; i++)
        {            
            switch (i)
            {
            case 0:
                if (cells[0] != -1)
                {
                    cells[0] = theMaze.getCell(y-1, x);
                }
                break;
            case 1:
                if (cells[1] != -1)
                {
                    cells[1] = theMaze.getCell(y, x-1);
                }
                break;
            case 2:
                if (cells[2] != -1)
                {
                    cells[2] = theMaze.getCell(y, x+1);
                }
                break;
            case 3:
                if (cells[3] != -1)
                {
                    cells[3] = theMaze.getCell(y+1, x);
                }
                break;           
            default:
                break;
            }
            //check if there is a reachable and unmarked cell;
            if (cells[i] != -1 && !theMaze.isMarked(cells[i]) && theMaze.canGo(endCell, cells[i]))
            {
                rc = runMaze(theMaze, path, startCell, cells[i]); 

                if (rc != 0) // if not encountered dead end, save the path. 
                {
                    path[rc] = endCell;
                    return rc + 1;
                }
                
            }
        }      
        //dead end. roll back.
        theMaze.unMark(endCell);
        return 0;
    }
}