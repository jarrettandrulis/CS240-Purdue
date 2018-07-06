
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int len = 0;
	while(s[len] != '\0') {
		len++;
	}
	
	return len;
}

char * mystrcpy(char * dest, char * src) {
	int i = 0;
	while(src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
	int destlen = 0;
	int i = 0;
	while(dest[destlen] != '\0')
		destlen++;
	while(src[i] != '\0') {
		dest[destlen] = src[i];
		destlen++;
		i++;
	}
	dest[destlen] = '\0';
	return dest; 
}

int mystrcmp(char * s1, char * s2) {
	int i = 0;
	while(s1[i] != '\0') {
		if(s1[i] > s2[i])
			return 1;
		else if(s1[i] < s2[i])
			return -1;			
		i++;
	}
	if(s2[i] != '\0') {
		if(s1[i] > s2[i])
			return 1;
		if(s1[i] < s2[i])
			return -1;
		}
	return 0;
}

char * mystrstr(char * hay, char * needle) {
	int i = 0;
	char *strBegin;
	while(hay[i] != '\0') {
		i++;
		if(hay[i] == needle[0]){
			int j = i;
			int k = 0;
			while(hay[j] == needle[k] && hay[j] != '\0' && needle[k] != '\0') {
				j++;
				k++;	
			}
			if(needle[k] == '\0') {
				return hay + i;
			}
		}
	}
	
	return NULL;
}

char * mystrdup(char * s) {
	char *dup = malloc(sizeof(s));
	int i = 0;
	while(s[i] != '\0') {
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return dup;
}

char * mymemcpy(char * dest, char * src, int n)
{
	int i = 0;
	while( i < n) {
		dest[i] = src[i];
		i++;
	}
	return dest;
}

