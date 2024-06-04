#include "board_graphics.h"


void board_printer(int board[ROW+2][COL+2]) {

	al_clear_to_color(al_color_name("black"));
	for (int i = 1; i < ROW+1; i++) { // Goes through each row
		for (int j = 1; j < COL+1; j++) { // Goes through each element
			if(board[i][j]){
				//printf("entre");
				al_draw_filled_rectangle(j*DISPLAY_X/COL, i*DISPLAY_Y/ROW, (j+1)*DISPLAY_X/COL, (i+1)*DISPLAY_X/ROW, al_color_name("white"));
			}
			printf("entre");
		}

	}

	al_flip_display();

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
