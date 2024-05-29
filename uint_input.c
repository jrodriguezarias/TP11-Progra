#include "constants.h"
#include <stdio.h>
#include "uint_input.h"
/*
Returns numerical value given from std input. If 'q' entered, returns END_PROG code.
If input makes no sense or is too big (overflow), returns respective error code.
*/


int get_input (void) {
    
	char c = getchar();
	int val;
	//value to be returned by get input
	switch(c) {
		case '\n':
			return 1;
			break;
		case 'q':
			val = END_PROG;
			break;
		default:
			val = (c>='0' && c<='9') ? (c-'0') : ERR_INPUT;
			//converts from char to int value of numbers, otherwise returns error.
			break;
	}
    
	while( (c = getchar()) != '\n') {
        
        	if(val >= 0 && c >= '0' && c <= '9') {
            
        		if( val > (int)(MAX_INT_VAL/10) )  {
                		val = ERR_OVERFLOW;
            		} else {
            			val = val*10 + (c-'0');
            			if(val < 0) {
            				val = ERR_OVERFLOW;
            			}
            		}
            
        	} else if(val != END_PROG && (c < '0' || c > '9') ) {
        		val = ERR_INPUT;
        	}

    	}
    
    return val;
    
}