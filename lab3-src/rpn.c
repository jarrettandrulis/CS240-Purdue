
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
  	double a, b, c;
	FILE *fd;
	fd = fopen(fileName, "r" );
	double lastnum;
	char * word;
	double arg1;
	double arg2;
    while ((word = nextword(fd))!=NULL){
			if(strcmp(word,"+") == 0){
				arg2 = stack_pop();
				arg1 = stack_pop();
				lastnum = arg1+arg2;
				stack_push(arg1+arg2);
			}
			else if (strcmp(word,"-") == 0) {
				arg2 = stack_pop();
				arg1 = stack_pop();
				lastnum = arg1-arg2;
				stack_push(arg1-arg2);
			}
			else if (strcmp(word,"*") == 0){
				arg2 = stack_pop();
				arg1 = stack_pop();
				stack_push(arg1*arg2);
			}	
			else if (strcmp(word,"/") == 0){
				arg2 = stack_pop();
				arg1 = stack_pop();
				lastnum = arg1/arg2;
				stack_push(arg1/arg2);
			}
			else if (strcmp(word,"sin") == 0){
				arg1 = stack_pop();
				stack_push(sin(arg1));
			}
			else if (strcmp(word,"cos") == 0){
				arg1 = stack_pop();
				stack_push(cos(arg1));
			}
			else if (strcmp(word,"pow") == 0){
				arg2 = stack_pop();
				arg1 = stack_pop();
				stack_push(pow(arg1,arg2));
			}
			else if (strcmp(word,"log") == 0){
				arg1 = stack_pop();
				stack_push(log(arg1));
			}
			else if (strcmp(word,"exp") == 0){
				arg1 = stack_pop();
				stack_push(exp(arg1));
			}
			else if(strcmp(word,"x") == 0){
				stack_push(x);
			}
			else{
				stack_push(atof(word));
			}
	}
	if(stack_top()>1){
		printf( "Elements remain in the stack\n");
		return NAN;
	}
	if(stack_top() < 1){
		printf("Stack underflow\n");
		return NAN;
	}
	return stack_pop();
}

