#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_DIGITS 32

// Problem (1/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting an integer
 *             base   -- the base of the number you are given
 * 
 * Return: The number as an integer
 *
 * Return Type: int
*****************************************************************************/
int pow(int base, int n)
{
	int num = 1;
	int i = 0;
	for(; i < n; i++)
	{
		num*=base;
	}
	return num;
}
int toInteger(char * number, int base) {
// Write Your Code Here
	int i = 0;
	int num = 0;
	int len = strlen(number);
	int arr[len];
	for(i = 0; i < len; i++)
	{
		if(isdigit(number[i]))
		{
			arr[i] = number[i] - '0';
		}
		else if(number[i] >= 'A' && number[i] <= 'F')
		{
			arr[i] = 10 + number[i] - 'A';
		}
	}
	for(i = len-1; i >=0; i--)
	{
		num+=arr[i]*(pow(base,((len-1)-i)));
	}

	return num;
}

// Problem (2/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting a string
 *             base   -- the base you are converting the numebr to
 * 
 * Return: The number as a string in base "base"
 *
 * Return Type: char *
*****************************************************************************/
char * reverse_str (char * str ) {
    int len = strlen(str);
    int i;
    for(i = 0; i<len/2;i++)
    {
       char c = str[i];
       str[i]=str[len-(i+1)];
       str[len-(i+1)]=c;
    }
    
    return str;
}
char * toBase(int number, int base) {
	char *num = malloc(sizeof(char)*32);
	int i = 0;
	int numb = 0;
	while(number > 0)
	{
		numb = number % base;
		if(numb>=10)
		{
			num[i] = numb-10+'A';
		}
		else if(numb < 10)
		{
			num[i] = numb+'0';
		}
		number/= base;
		i++;
	}
	num[i] = '\0';
	int len = strlen(num);
    for(i = 0; i<len/2;i++)
    {
       char c = num[i];
       num[i]=num[len-(i+1)];
       num[len-(i+1)]=c;
    }
	return num;
}
