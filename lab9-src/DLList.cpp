#include "DLList.h"

/**
 * @brief      Constructor for the DLList.
 */
DLList::DLList()
{
	/** @todo Write a constructor for a dllist. Check slides! **/
	DLNode * e = new DLNode();
	head = e;
	head->next = head;
	head->prev = head;
}

/**
 * @brief      Destructor for the DLList.
 */
DLList::~DLList()
{
	/** @todo Clean up your mess! **/
	delete head;
}

/**
 * @brief      Print the DLList line by line.
 */
void DLList::print()
{
	/** @todo Print this list line by line **/
	DLNode * e = head;
	e = e->next;
	while(e != head)
	{
		std::cout << e->data << std::endl;
		e = e->next;
	}
}

/**
 * @brief      Sort and print the list.
 * 
 * This function should sort and print the list.
 * Note: the actual list is NOT to be modified.
 * In other words, it should only *print* in a
 * sorted order, not actually sort the list.
 */
void DLList::printSorted()
{
	int len = 0;
	DLNode * e = head;
	e = e->next;
	while(e != head)
	{
		e = e->next;
		len++;
	}
	int * i = new int[len];
	e = head;
	e = e->next;
	for(int j = 0; j < len; j++)
	{
		i[j] = e->data;
		e = e->next;
	}
	for(int j = 0; j < len; j++){
		for(int k = 0; k < len; k++){
			if(i[j]< i[k])
			{
				int holder = i[j];
				i[j] = i[k];
				i[k] = holder;
			}
		}
	}
	for(int j = 0; j < len; j++)
		std::cout <<i[j] << std::endl;
}
/**
 * @brief      Add to the front of the list.
 *
 * @param[in]  data  Item to add to front.
 */
void DLList::insertFront(int data)
{
	DLNode * e = new DLNode();
	e->data = data;
	e->next = head->next;
	head->next->prev = e;
	e->prev = head;
	head->next = e;
}

/**
 * @brief      Removes & stores the last element.
 *
 * The last element is removed and stored in the
 * referenced variable data.
 * 
 * @param      data  Thing in which we are storing the data.
 *
 * @return     True upon successful removal.
 */
bool DLList::removeLast(int & data)
{
	/** @todo Remove the last thing **/
	data = head->prev->data;
	head->prev->prev->next = head;
	head->prev = head->prev->prev;
	return true;
}

/**
 * @brief      Difference of two lists.
 *
 * @param      list  Subtrahend.
 *
 * @return     Returns a pointer to the difference.
 */
DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	/** @todo Implement this function **/
	DLNode * e = head->next;
	DLNode * d = list.head->next;
	bool x = false;
	while(e != head)
	{
		x = true;
		d = list.head->next;
		while(d != list.head)
		{
			if(e->data == d->data)
				x = false;
			d = d->next;
		}
		if(x)
			diff->insertFront(e->data);
		e = e->next;
	}
	return diff;
}

/**
 * @brief      Returns a sublist of items in a range.
 *
 * @param[in]  start  First index.
 * @param[in]  end    Second index.
 *
 * @return     Elements between first and second index.
 */
DLList * DLList::getRange(int start, int end)
{
	DLList * range = new DLList();
	/** @todo getRange **/
	return range;
}

/**
 * @brief      Intersection of this list and another list.
 *
 * @param      list  The other list.
 *
 * @return     Elements list shares with this one.
 */
DLList * DLList::intersection(DLList & list)
{
	DLList * diff = new DLList();
	/** @todo Implement this function **/
	DLNode * e = head->next;
	DLNode * d = list.head->next;
	bool x = false;
	while(e != head)
	{
		x = false;
		d = list.head->next;
		while(d != list.head)
		{
			if(e->data == d->data)
				x = true;
			d = d->next;
		}
		if(x)
			
			{
				DLNode * c = new DLNode();
				c->data = e->data;
				c->next = diff->head;
				c->prev = diff->head->prev;
				diff->head->prev->next = c;
				diff->head->prev = c;
			}
		e = e->next;
	}
	return diff;
}

/**
 * @brief      Removes nodes in the start-end range.
 *
 * @param[in]  start  First node.
 * @param[in]  end    Second node.
 */
void DLList::removeRange(int start, int end)
{
	/** @todo Remove a range of elements **/
}
