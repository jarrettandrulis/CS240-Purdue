// Stack Implementation

// Used for cout << "string"
#include <iostream>

using namespace std;

#include "Stack.h"

// Constructor
Stack::Stack(int maxStack) {
	this->maxStack = maxStack;
	stack = new double[maxStack];
	top = 0;
}
	// Push a value into the stack.
	// Return false if max is reached.
	bool Stack::push(double value){
		if(maxStack == top)
		{
			return false;
		}
		stack[top++] = value;
		return true;
		
	
	}

	// Pop a value from the stack.
	// Return false if stack is empty
	bool Stack::pop(double & value){
		if(top==0) return false;
		value = stack[top-1];
		top-=1;
		return true;
	}

	// Return number of valuesmak in the stack
	int Stack::Stack::getTop() const{
		return top;
	}

	// Return max number of values in stack
	int Stack::getMaxStack() const{
		return maxStack;
	}

	// Prints the stack contents
	void Stack::print() const{
		cout << "Stack:" << endl;
		for(int i = 0; i < top; i++)
		{
			cout << i << ":" << stack[i] << endl;
		}
		cout << "------" << endl;
	}
	
	Stack::~Stack()
	{
		delete [] stack;
	}

// Write other calls here

