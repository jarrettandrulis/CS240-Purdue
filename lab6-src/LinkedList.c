
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
		ListNode * e;

	if (list->head == NULL) {
		return 0;
	}

	int x = 0;

	e = list->head;
	while (e != NULL) {
		if(e->value==value)
			x = 1;
		e = e->next;
	}
	
	
	return x;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	while (e->next != NULL) {
		ListNode * j = e->next;
		if(j->value==value){
			e->next=e->next->next;
			return 1;
		}
		e = e->next;
		
	}
	return 0;
	
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	int i;
	for(i = 0; i < ith; i++)
	{
		if(e==NULL) return 0;
		e = e->next;
	}
	*value = e->value;
	return 1;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	int i;
	for(i = 0; i < ith-1; i++)
	{
		if(e->next==NULL) return 0;
		e = e->next;
	}
	e->next=e->next->next;
	return 1;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	int i = 0;
	while(e!=NULL)
	{
		e = e->next;
		i++;
	}
	return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	FILE * fout;
	fout = fopen(file_name,"w+");
	if(fout ==NULL) return 0;
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	while(e!=NULL)
	{
		int d = e->value;
		fprintf(fout,"%d\n",d);
		e = e->next;
	}
	fclose(fout);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	ListNode * e;
	ListNode * d;
	llist_clear(list);

	FILE * fin;
	fin = fopen(file_name,"r");
	if(fin ==NULL) return 0;
	int num = 0;
	fscanf(fin,"%d",&(num));
	e = malloc(sizeof(ListNode));
	list->head = e;
	e->value = num;
	while(fscanf(fin,"%d",&(num)) == 1)
	{
		d = malloc(sizeof(ListNode));
		d->next = e;
		d->value = num;
		list->head = d;
		e = d;
	}
	
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order is ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	ListNode * e;
	ListNode * d;

	if (list->head == NULL) {
		return 0;
	}
	e = list->head;
	d = list->head;
	int i = 0;

	while(e->next!=NULL)
	{
		e = e->next;
		i++;
	}
	e = d->next;
	int j,k;
	for(j = 0; j < i; j++)
	{
		d = list->head;
		e = d->next;
		for(k = 0; k < i; k++)
		{
			if(ascending && e->value < d->value)
			{
				int hold = e->value;
				e->value = d->value;
				d->value = hold;
			}
			if(!ascending && e->value > d->value)
			{
				int hold = e->value;
				e->value = d->value;
				d->value = hold;
			}
			e = e->next;
			d = d->next;
		}
	}

}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * e;
	ListNode * d;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	d = e->next;
	list->head=d;
	* value = e->value;
	free(e);
	
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
  	ListNode * e;
	if (list->head == NULL) {
		return 0;
	}
	if(list->head->next== NULL)
	{
		value = list->head->value;
		list->head == NULL;
		llist_clear(list);
		return 0;
	}
	e = list->head;
	while(e->next->next!=NULL)
	{
		e = e->next;
	}
	*value = e->next->value;
	free(e->next);
	e->next= NULL;


	
	return 1; 
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	ListNode * e = malloc(sizeof(ListNode));
	e->value = value;
	ListNode *hold;
	hold = list->head;
	list->head=e;
	e->next= hold;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	while(e->next!=NULL)
	{
		e = e->next;
	}
	ListNode * c = malloc(sizeof(ListNode));
	c->value = value;
	e->next=c;
	

}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
	ListNode * e;

	if (list->head == NULL) {
		return 0;
	}


	e = list->head;
	ListNode * d;
	while(e!=NULL)
	{
		d = e->next;
		free(e);
		e = d;
	}
	list->head=NULL;
}
