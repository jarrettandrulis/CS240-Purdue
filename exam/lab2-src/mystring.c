
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int len = 0;
	while(*s!='\0')
	{
		*s++;
		len++;
	}

	return len;
}

char * mystrcpy(char * dest, char * src) {
	int len = 0;
	while(src[len]!='\0')
	{
		len++;
	}
	dest = malloc(sizeof(char)*(len+1));
	int i;
	for( i = 0; i < len; i++ )
	{
		dest[i]=src[i];
	}
	dest[i]='\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
	return NULL;
}

int mystrcmp(char * s1, char * s2) {
	return -1;
}

char * mystrstr(char * hay, char * needle) {
	return NULL;
}

char * mystrdup(char * s) {
	return NULL;
}

char * mymemcpy(char * dest, char * src, int n)
{
	return NULL;
}

