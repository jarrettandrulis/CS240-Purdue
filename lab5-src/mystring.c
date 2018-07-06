
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
	int len = 0;
	while(*s != '\0')
	{
		len++;
		s++;
	}
	
	return len;
}

char * mystrcpy(char * dest, char * src) {
	int len = 0;	
	while(*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		len++;
	}
	*dest = '\0';
	return dest-len;
}

char * mystrcat(char * dest, char * src) {
	int len = 0;
	while(*dest != '\0')
	{
		dest++;
		len++;
	}
		while(*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		len++;
	}
	*dest = '\0';
	return dest - len;
}

int mystrcmp(char * s1, char * s2) {
	while(*s1 != '\0')
	{
		if(*s1 > *s2) return 1;
		if(*s2 > *s1) return -1;
		s1++;
		s2++;
	}
		if(*s1 > *s2) return 1;
		if(*s2 > *s1) return -1;
	return 0;
}

char * mystrstr(char * hay, char * needle) {
	int needleLen = mystrlen(needle);
	char * hay2 = hay; 
	char * needle2 = needle;
	while(*hay != '\0'){
		
		if(*hay2==*needle2)
		{
			while(*hay2==*needle2){
				hay2++;
				needle2++;
			}
			if(*needle2=='\0')
				return hay;
		}
		
		needle2 = needle;
		hay2 = hay;
		hay++;
		hay2++;
	}
	return NULL;
}

char * mystrdup(char * s) {
	int len = mystrlen(s);	
	char * c = (char *)malloc(sizeof(char)*len);
	while(*s!='\0')
	{
		*c=*s;
		c++;
		s++;
	}
	return c - len;
	return NULL;
}

char * mymemcpy(char * dest, char * src, int n)
{
	int i = 0;
	for( i = 0; i < n; i++,dest++,src++){
		*dest = *src;
	}
	return dest-n;
}

