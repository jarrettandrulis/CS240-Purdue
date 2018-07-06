/*
 *  CS 24000 First mid-semester exam.
 *   Problem #29
 *
 *   unsigned int emptyLinesCounter(const char * str)
 *
 *  Arguments:
 *		char * str -- a pointer to a string
 *		
 *  Description:
 *		Given a string of input, counts number of empty lines in str. An
 *		empty line is defined as a line that contain no character except for newline 
 *		('\n') character or that may contain only white spaces (' ', '\t', '\r') 
 *		and a newline character ('\n'))
 *
 */

 /* ======================== Start your edits here =========================== */
 
 /*
  *  NOTE NOTE NOTE NOTE NOTE
  *  You are not allowed to add any other libraries or library includes in addition
  *   to <stdlib.h> other than <math.h> (if you believe you need it).
  */
 #include <stdlib.h>
 
 /* 
  * Complete the function below for the exam
  */

unsigned int emptyLinesCounter(const char * str)
 {
	int stringCounter = 0;
	int lineCounter = 0;
	char lastChar;
	int hasChar = 0;
	while(1)
	{
		lastChar = str[stringCounter++];
		if(lastChar == '\n')
			{
				if(hasChar == 0){
					lineCounter++;
				}
				hasChar = 0;
			}
		if(lastChar != ' ' && lastChar != '\t' && lastChar != 
'\r' && lastChar != '\n')
			hasChar = 1;
		if(lastChar == '\0')
			break;
	}
	
	return lineCounter;
 }
  
 /* ======================== End your edits here =========================== */

 /*
 ************************************************************************
  *  Do NOT change any of the lines between here and the end of the file!
 ************************************************************************
  */

#include <stdio.h>
#include <assert.h>

char *Usage = "Usage: %s <string>\n";

int main(int argc, char *argv[])
{
	unsigned int result;
	
	if (argc != 2) 
	{
		fprintf(stderr, Usage, argv[0]);
		exit(1);
	}
	
	result = emptyLinesCounter(argv[1]);
	printf("Empty lines: %u\n", result);
	
	return 0;
}
	
	
