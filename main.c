#include <stdio.h>
#include "constants.h"
#include "uint_input.h"
#include "Rules.h"
#include "board_graphics.h"

/*
2 boards are defined to save the initial iteration in board_i and the future generation in board_f. 
The '+2' that accompanies ROW and COL is put in place to ensure the board has a perimeter of zeroes which are used for calculating cell states and are not displayed.
*/
int board[2][ROW+2][COL+2];


int main (void) {
	
	printf("\nBienvenido al juego de la vida de Conway. El tablero tendrá %d filas y %d columnas.\n\n", ROW, COL);
	printf("Ingrese el estado inicial que desee.\nLos 0 y los espacios serán tomados como muertas.\nCualquier otro valor sera considerado vivo. Ingrese los caracteres sin espacios entremedio.\n(Si ingresa caracteres de mas se ignoraran; si ingresa de menos quedaran muertas)\n");		
	
	get_board(board[0]);
	
	printf("\n\nEstado inicial:\n");
	board_printer(board[0]);
	printf("\n\n");

	int input;
	do {
		printf("Seleccione cuantas generaciones avanzar (puede avanzar una generacion presionando enter o puede finalizar el programa ingresando 'q'): ");
		input = get_input();
		
		switch(input) {
			case 0:
			case ERR_INPUT:
				printf("Formato invalido, por favor ingrese un entero positivo\n");
				break;
			case ERR_OVERFLOW:
				printf("Numero demasiado grande, ingrese un numero <= %d\n", MAX_INT_VAL);
				break;
			case END_PROG:
				printf("Programa finalizado. ¡Gracias por jugar!\n");
				break;
			default:
				int i;
				int current = 0;
				for(i = 0; i < input; i++) {
					new_board(board[current], board[!current]);
					current = !current;
				}
				printf("\n\nTablero en %d ", input);
				if (input == 1){
					printf("generacion: \n\n");
				} else {
					printf("generaciones: \n\n");
				}
				board_printer(board[current]);
				printf("\n");
		}

	} while(input!=END_PROG);
	
	return 0;
}