
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  top = 0;
}

double stack_pop()
{
	top--;
	return stack[top];
	
}

void stack_push(double val)
{
	stack[top++] = val;
}

void stack_print()
{
	int i = 0;
	printf("Stack:\n");
	while(i<top)
	{
		printf("%d: %f\n",i,stack[i]);
		i++;
	}
	if(top == 0)
		printf("Stack is empty");
}

int stack_top()
{
  return top;
}

int stack_max()
{
  return MAXSTACK;
}

int stack_is_empty()
{
  return top == 0;
}


