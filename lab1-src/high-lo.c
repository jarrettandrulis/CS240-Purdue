#include <stdio.h>

int main() {
	printf("Welcome to the High Low game...\n);
	printf("Think of a number between 1 and 100 and press <enter>");
	int max = 100;
	int min = 1;
	while(getchar() != '\n');
	while(higher!=lower)
	{
		int guess = (min+max)/2;
		printf("Is it higher than %d? (y/n)\n",guess);
		if(getchar() = 'y')
			min = guess;
		else
			max = guess;
	}
	printf(">>>>>> The number is %d",max);

}
