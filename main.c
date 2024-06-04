#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
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


		ALLEGRO_DISPLAY * display = NULL;
		ALLEGRO_FONT * font;

		int redraw = 0;
		int do_exit = 0;
		int keyBeingPressed = 0;
		int keyPressed = 0;
		unsigned long int number = 0;
		char str[30];
		int digitNum = 0;
		int leftClick = 0;
		int x = 0;
		int y = 0;
		int enterPressed = 0;
		int currentMap = 0;
		int current = 0;

		if(!al_init()){
		    	fprintf(stderr, "failed to initialize allegro!\n");
		    	return -1;
		}
		if (!al_install_keyboard()) {
		    fprintf(stderr, "failed to initialize the keyboard!\n");
		    return -1;
		}

		    display = al_create_display(DISPLAY_X, DISPLAY_Y);

		    if(!display){
		        	fprintf(stderr, "failed to create\n");
		        	return -1;
		    }

		    ALLEGRO_EVENT_QUEUE * event_queue;
		    event_queue = al_create_event_queue();
		    if (!event_queue) {
		        printf("failed to create event_queue!\n");
		        al_destroy_display(display);
		        return -1;
		    }

		    ALLEGRO_TIMER * timer;
		    timer = al_create_timer(1.0 / 60);

		    al_init_font_addon();

		    font = al_create_builtin_font();
		    if (!font) {
		    	printf("failed to create event_queue!\n");
		    	al_destroy_display(display);
		    	return -1;
		    }

		    if (!al_install_mouse()) {
		            printf("failed to initialize the mouse!\n");
		            return -1;
		        }

		    if (!al_init_primitives_addon()) {
		                printf("failed to initialize primitives!\n");
		                return -1;
		            }

		    al_register_event_source(event_queue, al_get_display_event_source(display));
		    al_register_event_source(event_queue, al_get_timer_event_source(timer));
		    al_register_event_source(event_queue, al_get_keyboard_event_source());
		    al_register_event_source(event_queue, al_get_mouse_event_source());

		    al_start_timer(timer);


		    al_clear_to_color(al_map_rgb(0, 0, 0));
		    for(int i = 0 ; i <= 10; i++){
		    	al_draw_line(i * DISPLAY_X/10, 0, i * DISPLAY_X/10, DISPLAY_Y, al_map_rgb(255, 255, 255), 2.0);
		    	al_draw_line(0, i * DISPLAY_Y/10, DISPLAY_X, i * DISPLAY_Y/10, al_map_rgb(255, 255, 255), 2.0);
		    }


		    al_flip_display();

		    while(!do_exit){
		    	ALLEGRO_EVENT ev;
		    	if(al_get_next_event(event_queue, &ev)){

		    		if(ev.type == ALLEGRO_EVENT_TIMER){

		    			switch (currentMap){
		    				case(0):
		    					//estoy en el selector de celdas vivas
								if (leftClick == 1){
									leftClick = 0;
									board[0][y][x] = !board[0][y][x]; // Cambiar el valor
									al_draw_filled_rectangle((x-1)*DISPLAY_X/10, (y-1)*DISPLAY_Y/10, (x)*DISPLAY_X/10, (y)*DISPLAY_Y/10, (board[0][y][x] ? al_color_name("white") : al_color_name("black")));
									al_flip_display();
								}
		    					if(keyBeingPressed && enterPressed){
		    						currentMap = 1;
		    						keyBeingPressed = 0;
		    						enterPressed = 0;
		    					}

		    					break;
		    				case(1):
		    					//generaciones
								if (keyBeingPressed && !enterPressed){
									number = number*10 + keyPressed;
									str[digitNum] = keyPressed + '0';
									digitNum++;
									str[digitNum] = '\0';
									//al_draw_filled_rectangle(0, DISPLAY_Y - DISPLAY_Y/(10*2), DISPLAY_X, DISPLAY_Y, al_color_name("white"));
									//al_draw_text(font, al_map_rgb_f(255, 255, 255), DISPLAY_X, DISPLAY_Y, ALLEGRO_ALIGN_RIGHT, strcat("Generations: ", str));
									//al_flip_display();
									keyBeingPressed = 0;
						    	}
		    					if (keyBeingPressed && enterPressed){
		    						enterPressed = 0;
		    						//printf("%s\n", str);

		    						for(int i = 0; i <= number; i++) {
		    							new_board(board[current], board[!current]);
		    							current = !current;
		    						}

		    						//board printer


		    						al_clear_to_color(al_color_name("black"));
		    						for(int i = 0 ; i <= 10; i++){
		    						    al_draw_line(i * DISPLAY_X/10, 0, i * DISPLAY_X/10, DISPLAY_Y, al_map_rgb(255, 255, 255), 2.0);
		    						    al_draw_line(0, i * DISPLAY_Y/10, DISPLAY_X, i * DISPLAY_Y/10, al_map_rgb(255, 255, 255), 2.0);
		    						}

		    						for (int i = 1; i < ROW+1; i++) { // Goes through each row
		    							for (int j = 1; j < COL+1; j++) { // Goes through each element
		    								if(board[current][i][j] == 1){
		    									al_draw_filled_rectangle(j*DISPLAY_X/COL, i*DISPLAY_Y/ROW, (j+1)*DISPLAY_X/COL, (i+1)*DISPLAY_X/ROW, al_color_name("white"));
		    								}
		    							}

		    						}

		    						al_flip_display();

		    						//board_printer2(board[current]);
		    						number = 0;
		    					}


		    					break;
		    				case(2):
		    					//ya veo las generaciones
		    					break;


		    			}

		    			//que hacer cada segundo


		    		}
		    		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
		    			do_exit = true;
		    		}
		    		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		    			leftClick = 1;
		    		}
		    		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
		    			leftClick = 0;
		    		}
		    		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
		    			x = (ev.mouse.x / (DISPLAY_X/COL)) + 1;
		    			y = (ev.mouse.y / (DISPLAY_Y/ROW)) + 1;
		    		}
		    		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

		    			switch(ev.keyboard.keycode){
		    				case ALLEGRO_KEY_0:
		    					keyPressed = 0;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_1:
		    					keyPressed = 1;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_2:
		    					keyPressed = 2;
		    					keyBeingPressed = 1;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_3:
		    					keyPressed = 3;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_4:
		    					keyPressed = 4;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_5:
		    					keyPressed = 5;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_6:
		    					keyPressed = 6;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_7:
		    					keyPressed = 7;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_8:
		    					keyPressed = 8;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_9:
		    					keyPressed = 9;
		    					keyBeingPressed = 1;
		    					break;
		    				case ALLEGRO_KEY_ENTER:
		    					enterPressed = 1;
		    					keyBeingPressed = 1;
		    					break;
		    			}

		    		}
		    	}
		    }

		    al_destroy_display(display);




	/*
	printf("\nBienvenido al juego de la vida de Conway. El tablero tendrá %d filas y %d columnas.\n\n", ROW, COL);
	printf("Ingrese el estado inicial que desee.\nLos 0 y los espacios serán tomados como muertas.\nCualquier otro valor sera considerado vivo. Ingrese los caracteres sin espacios entremedio.\n(Si ingresa caracteres de mas se ignoraran; si ingresa de menos quedaran muertas)\n");

	get_board(board[current]); // Every board/matrix functions should be used like this

	// Getting initial Conway board from user
	printf("\n\nEstado inicial:\n");
	board_printer(board[0]);
	printf("\n\n");


	int input;

	do {
		// Getting number of generations from user
		printf("Seleccione cuantas generaciones avanzar (puede avanzar una generacion "
		"presionando enter o puede finalizar el programa ingresando 'q'): ");
		input = get_input();

		// Filtering error cases
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

			// Updating and printing Conway board
			default:
				int i;
				for(i = 0; i < input; i++) {
					new_board(board[current], board[!current]);
					current = !current;
				}

				printf("\n\nTablero en %d generacion%s: \n\n", input, 1==input ? "es" : "");
				board_printer(board[current]);
				printf("\n");
		}

	} while(input!=END_PROG);
	*/
	return 0;
}


void board_printer2(int board[ROW+2][COL+2]) {

	for (int i = 1; i < ROW+1; i++) { // Goes through each row

		for (int j = 1; j < COL+1; j++) { // Goes through each element
			printf("| %c ", board[i][j] ? 'X' : ' ');
		}

		printf("|\n"); // "Closes" the row

	}

}
