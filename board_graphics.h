#ifndef BOARD_GRAPHICS_H
#define BOARD_GRAPHICS_H

#include <stdio.h>
#include "constants.h"

#ifndef ALIVE_CHAR
    #define ALIVE_CHAR(c) ( (c) != ' ' && (c) != '0' )
#endif

void board_printer (int board[ROW+2][COL+2]);
/*
Board_printer is designed to print a 2D matrix.
This means that, when using a 3D matrix as a parameter, the first value has to be specified. 
*/

void get_board(int board[ROW+2][COL+2]);
/*
Gets a binary board from std input, interpreting the char dead as 0
*/

#endif // BOARD_GRAPHICS_H