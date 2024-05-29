PARAM := -g -Wall # Compilation parameters that are utilized every time gcc is invoked
NAME := conway_gol # Name of the executable

${NAME}: Rules.o uint_input.o board_graphics.o main.o
	gcc Rules.o uint_input.o board_graphics.o main.o -o ${NAME} ${PARAM} # Executable. Includes all of the following modules

Rules.o: Rules.c constants.h
	gcc Rules.c -c ${PARAM} # Module with the rules of the Game of Life. Receives a board state and returns the next generation

uint_input.o: uint_input.c constants.h uint_input.h
	gcc uint_input.c -c ${PARAM} # Input module that has all of the UI that allows the user to input the initial board state	

board_graphics.o: board_graphics.c constants.h board_graphics.h
	gcc board_graphics.c -c ${PARAM} # Graphics module responsible for printing the board state

main.o: main.c constants.h Rules.h uint_input.h board_graphics.h
	gcc main.c -c ${PARAM} # Module containing the main program flow within the main function

clean: 
	rm *.o	# Clears all .o (object code) files



