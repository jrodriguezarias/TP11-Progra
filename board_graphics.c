#include "board_graphics.h"

void board_printer(int board[ROW+2][COL+2]) {

	for (int i = 1; i < ROW+1; i++) { // Goes through each row

		for (int j = 1; j < COL+1; j++) { // Goes through each element
			printf("| %c ", board[i][j] ? 'X' : ' ');
		}

		printf("|\n"); // "Closes" the row

	}

}



void get_board(int board[ROW+2][COL+2]) {
    
    for(int i = 1; i < ROW+1; i++) {
		char c;
		int j = 1; // Counts the number of elements
		printf ("%d: ",i);
        
		while((c=getchar()) != '\n') { // Goes through the i-th line
			if(j<COL+1) {
				board[i][j] = ALIVE_CHAR(c);
			}
			j++;
		}
        
	}
    
}