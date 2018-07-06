
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c;
	
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
	c = 0;
	int d = 0;
	int v = 0;
	word[0] = '\0';
	while((d = fgetc(fd))!=EOF)
		{
			if(d == ' ' || d == '\n' || d ==  '\t' || d ==  '\r')
				{
					if(word[0] == '\0')
						continue;
					else
						break;
				}
			v++;	
			word[c] = d;		
			c++;
		}
	word[c] = '\0';
	if(v)
	{
		return word;
	}
	return NULL;
}

