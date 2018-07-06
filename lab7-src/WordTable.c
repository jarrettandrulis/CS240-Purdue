
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	int i;
	for (i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			if(!llist_exists(&wtable->wordArray[i].positions,position))
				llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}
 
	// Word not found.
	if(wtable->nWords == wtable->maxWords)
	{
		wtable->maxWords*=2;
		wtable->wordArray = (WordInfo *) realloc(wtable->wordArray ,wtable->maxWords * sizeof(WordInfo));
	}
	

	// Make sure that the array has space.
	// Expand the wordArray here.

	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	// Write your code here
		for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			return &(wtable->wordArray[i].positions);
		}
	}

}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
int inAlphabet(char c)
{
	if((c >= 'A' && c <='Z')||(c >= 'a' && c <='z'))
		return 1;
	return 0;
}
static char * nextword(FILE * fd) {
		char c = fgetc(fd);
		charCount++;
		wordPos+=wordLength;	
		wordLength = 0;
		wordLength++;
		int i = 0;
		while(c != EOF && !inAlphabet(c))
		{
			c = fgetc(fd);
			charCount++;
			wordLength++;
			
		}
		wordLength++;
		if(c == EOF)
			return NULL;
		while(inAlphabet(c))
		{
			word[i++] = c;
			c = fgetc(fd);
			wordLength++;
			charCount++;
		}
		word[i] = '\0';
        toLower(word);
		
		return word;
}

// Convert string to lower case
void toLower(char *s) {
	while(*s != '\0')
	{
		if(*s >= 'A' && *s <= 'Z')
		{
			*s+='a'-'A';
		}
		*s++;
	}
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	wtable_init(wtable);
	wordPos = 0;
	charCount = 0;
	wordLength = 0;
	FILE * fd = fopen(fileName,"r");
	int i = 0;
	char * word;
	if(fd == NULL)
		return 0;
	while(1)
	{
		word = nextword(fd);
		if(word == NULL) break;
		if(verbose)
		{
			printf("%d: word=%s, pos=%d\n",i,word,ftell(fd)-strlen(word)-1);
		}
		wtable_add(wtable,word,ftell(fd)-strlen(word)-1);



		i++;
	} 
	return 0;

}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	for (int i = 0; i < wtable->nWords; i++) {
		for(int j = i+1; j < wtable->nWords; j++)
		{
			if(strcmp(wtable->wordArray[i].word,wtable->wordArray[j].word)>0)
			{
				WordInfo e = wtable->wordArray[i];
				wtable->wordArray[i] = wtable->wordArray[j];
				wtable->wordArray[j] = e;
			}
		}
	}
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	FILE * fd = fopen(fileName,"r");
	printf("===== Segments for word \"%s\" in book \"sagan.txt\" =====\n",word);
	LinkedList * ll;
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			*ll = wtable->wordArray[i].positions;
		}
	}
	
	ListNode * e;
	e = ll->head;
	char * string = malloc(sizeof(char)*201);
	while(e!=NULL)
	{
		fseek(fd,e->value,SEEK_SET);
		for(int j = 0; j < 200; j++)
		{
			char c = fgetc(fd);
			if(c==NULL || c==EOF) break;
			string[j] = c;
		} 
		string[200] = '\0';
		printf("---------- pos=%d-----\n......%s......\n",e->value,string);
		e = e->next;
	}
	


}

