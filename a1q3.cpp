#include "wall.h"
#include "maze.h"
#include <iostream>

int runMaze(Maze& theMaze, int path[], int startCell, int endCell){
    std::cout << startCell << "-" << endCell <<std::endl;
    int rc = 0;
	auto x = theMaze.getCol(endCell);
    auto y = theMaze.getRow(endCell);
    auto xEdge = theMaze.numCols()-1;
    auto yEdge = theMaze.numRows() -1;
    theMaze.mark(endCell); //mark current cell.
    if (startCell == endCell)
    {
        path[0] = startCell;
        return 1;
    }else{
        // A* 
        // cell identifies, X is current:
        // 0 1 2
        // 3 X 4
        // 5 6 7
        int cells[8]{0};
        if (x == 0) //left xEdge
        {
            cells[0] = -1;
            cells[3] = -1;
            cells[5] = -1;
        }
        if (x == xEdge) //right xEdge
        {
            cells[2] = -1;
            cells[4] = -1;
            cells[7] = -1;
        }
        if (y == 0) //top yEdge
        {
            cells[0] = -1;
            cells[1] = -1;
            cells[2] = -1;
        }
        if (y == yEdge) //bottom yEdge
        {
            cells[5] = -1;
            cells[6] = -1;
            cells[7] = -1;
        }
        //so far, the value in cells[n] which is not -1 means there is a cell at cells[n];
        // 0 1 2
        // 3 X 4
        // 5 6 7
        for (size_t i = 0; i < 8; i++)
        {            
            switch (i)
            {
            case 0:
                if (cells[0] != -1)
                {
                    cells[0] = theMaze.getCell(y-1, x-1);
                }
                break;
            case 1:
                if (cells[1] != -1)
                {
                    cells[1] = theMaze.getCell(y-1, x);
                }
                break;
            case 2:
                if (cells[2] != -1)
                {
                    cells[2] = theMaze.getCell(y-1, x+1);
                }
                break;
            case 3:
                if (cells[3] != -1)
                {
                    cells[3] = theMaze.getCell(y, x-1);
                }
                break;           
            case 4:
                if (cells[4] != -1)
                {
                    cells[4] = theMaze.getCell(y, x+1);
                }
                break;
            case 5:
                if (cells[5] != -1)
                {
                    cells[5] = theMaze.getCell(y+1, x-1);
                }
                break;
            case 6:
                if (cells[6] != -1)
                {
                    cells[6] = theMaze.getCell(y+1, x);
                }
                break;
            case 7:
                if (cells[7] != -1)
                {
                    cells[7] = theMaze.getCell(y+1, x+1);
                }
                break; 
            default:
                break;
            }
            //check if there is another reachable and unmarked cell;
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
        if (rc == 0) //dead end. roll back.
        {
            theMaze.unMark(endCell);
            return 0;
        }
    }
}