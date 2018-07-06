#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Problem (1/4)
/******************************************************************************
 * TODO: Print the array.
 *       The format should be (array index)(colon)(array element)(newline) 
 * 
 * Parameters: n -- the number of elements in the array
 *             array -- a double array
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void printArray(int n, double * array) {
// Write Your Code Here
    int i;
    for( i = 0; i < n; i++)
    {
        printf("%d:%f\n",i,*(array+i));
    }
}

// Problem (2/4)
/******************************************************************************
 * TODO: Return the minimum element of array 
 * 
 * Parameters: array -- a double array
 *             n -- the number of elements in the array
 *
 * Return: minimum element in array 
 *
 * Return Type: double
 *****************************************************************************/
double minArray(int n, double * array) {
    int i;
    int min = *array;
    for( i = 0; i < n; i++)
    {
        if(min>*(array+i))
        {
            min = *(array+i);
        }
    }
	return min;
}

// Problem ( 3/4 ) 
/******************************************************************************
 * TODO: Reverse the given string 'str'. 
 * E.g. reverse_str("smile") should return "elims"
 * 
 * Parameters: str -- The given string to be reversed.
 *
 * Return: A pointer to str, str should be reversed 
 *
 * Return Type: char pointer
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

// Problem ( 4/4 ) 
/******************************************************************************
 * TODO: Determine if the string str2 is a permutation of str1. A permutation
 * is the rearranging of characters in a different order. 
 * E.g. the string "act" is a permutation of "cat" 
 *
 * Hint: count the occurences of each letter
 * 
 * Parameters: str1 -- The original string
 *	       str2 -- Determine if this string is a permutation of str1 
 *
 * Return: 1 if str2 is a permutation
 *         0 if str2 is not a permutation
 *
 * Return Type: integer
 *****************************************************************************/
int is_permutation ( char * str1, char * str2 ) {
    int chars[26] = {};
    int i = 0;
    for(i = 0; i < strlen(str1); i++)
    {
        chars[(str1[i]-'a')]++;
    }
    for(i = 0; i < strlen(str2); i++)
    {
        chars[(str2[i]-'a')]--;
    }
    for(i = 0; i < 26; i++)
    {
        if(chars[i]!=0)
            return 0;
    }
    return 1;
}
