#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	if(ascending == 0){
		for(int i = 0; i < n; i++)
   		{
			for(int j = i; j < n; j++)
			{
				void * x = (void *)((char *)array+i*elementSize);
				void * y = (void *)((char *)array+j*elementSize);

				if(((*compFunc)(x,y)<0))
				{
					void * temp = malloc(elementSize);
					memcpy(temp,x,elementSize);
					memcpy(x,y,elementSize);
					memcpy(y,temp,elementSize);
				}
			}
		}
	}
	else {
		for(int i = 0; i < n; i++)
   		{
			for(int j = 0; j < i; j++)
			{
				void * x = (void *)((char *)array+i*elementSize);
				void * y = (void *)((char *)array+j*elementSize);

				if((*compFunc)(x,y)<0)
				{
					void * temp = malloc(elementSize);
					memcpy(temp,x,elementSize);
					memcpy(x,y,elementSize);
					memcpy(y,temp,elementSize);
				}
			}
		}
	}

}

