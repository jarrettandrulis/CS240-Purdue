
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv) {
	int c;
	int lines=0;
	FILE *file;
	file = fopen(argv[1],"r");
	while(( c = getc(file)) != EOF)
		{
			if( c == '\n')
				lines++;
		}
 	printf("Program that counts lines.\n");
	printf("Total lines: %d\n", lines);

	exit(0);
}
