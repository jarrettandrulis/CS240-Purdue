#include <stdio.h>

int main() {
	printf("Welcome to the High Low game...\n");
	while(1)
	{
		printf("Think of a number between 1 and 100 and press <enter>");
		int max = 100;
		int min = 1;
		while(getchar() != '\n');
		while(min <= max)
		{
			int guess = (min+max)/2;
			printf("Is it higher than %d? (y/n)\n",guess);
			char c = getchar();
			if(c == 'y')
				min = guess+1;
			else if(c == 'n')
				max = guess-1;
			else
				printf("Type y or n\n");
			getchar();
		}
		printf("\n>>>>>> The number is %d\n",min);
		printf("\nDo you want to continue playing (y/n)?");
		if(getchar() == 'n')
		{
			printf("Thanks for playing!!!\n");
			break;
		}
		getchar();
	}

}
