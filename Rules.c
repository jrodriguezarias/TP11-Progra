#include "constants.h"
#define IS_ALIVE(c,v) (((c)==1)? ((v)==2 || (v)==3):((v)==3))
/* this macro returns 1 if the cell is alive and 0 if the cell dies based on the number of neighbours replacing the old funtion, "IS_ALIVE"
*/

static int live_cells(int x, int y, int board[ROW+2][COL+2]);
/* Returns amount of alive cells around the cell in the specified position. This function is defined as static as it is only used inside this module*/

void new_board(int board[ROW+2][COL+2], int nboard[ROW+2][COL+2]);
/*
This function will use the current generation to build the new generation on the other 1st axis value.
The function contains a static variable that saves which is the current generation.
This static variable's value is what the function returns.
*/




static int live_cells(int x, int y, int board[ROW + 2][COL + 2]){

	int vivas = 0;
	int f, c;
	for(f = (y-1) ; f < (y+2) ; f++){
		for(c = (x-1) ; c < (x+2) ; c++){
			if(f == y && c == x){
				continue;
			} else {
				vivas += board[f][c];
			}	
			
			/*
			Counts the number of cells alive arround a cerain position, this will be used as v, in IS_ALIVE
			*/
		}	
	}
	return vivas;
}





void new_board(int board[ROW+2][COL+2],int nboard[ROW+2][COL+2]) { 
	int f, c;
	
	for(f = 1 ; f < ROW + 1 ; f++) {
		for(c = 1 ; c < COL + 1 ; c++) {

			nboard[f][c] = IS_ALIVE(board[f][c], live_cells(c, f, board));		
		//fills nboard with actual state of cells
		}
	}
	//As it modiffies an array no parameter needs to be returned
}

