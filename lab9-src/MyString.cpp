
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include "MyString.h"
// My own implementation of strlen
int
MyString::slength(const char *s) const
{
	int i = 0;
 while(*s != '\0')
  {
  	*s++;
    i++;
    if(i > 50) return 0;
  }
  return i;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
  // Add implementation here
  // Allocate memory for _s.

  // Copy s into _s
  _s = new char[slength(s)];
  for(int i = 0; i <= slength(s); i++)
  {
  	_s[i] = s[i];
  }
  
}


// Create a MyString from a C string
MyString::MyString(const char * s)
{
  initialize(s);
}


// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  _s = new char[1];
  *_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  if (this != &other) // protect against invalid self-assignment
  {
    // deallocate old memory
    delete [] _s;

    // Initialize _s with the "other" object.
    initialize(other._s);

    // by convention, always return *this
    return *this;
  }
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
  // Add implementation here

  // Make sure that i is not beyond the end of string

  // Allocate memory for substring

  // Copy characters of substring
  MyString sub = MyString();
  if(i > length()) return sub;
  sub._s = new char[n];
  for(int j = i; j < i+n; j++)
  {
    if(j > length()) break;
    sub._s[j-i] = _s[j];

  }

  // Return substring
  return sub;
}

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
  // Add implementation here

  // If i is beyond the end of string return
  if(i > length()) return ;
  if(i+n > length())
  {
    n = length()-i;
  }

  for(int j = i; j < i+n; j++)
  {
    _s[i] = _s[i+1];
    for(int k = i+1; k < length(); k++)
    {
      _s[k] = _s[k+1];
    }

  }

  // Remove characters
  
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
  if(length() != s.length()) return false;
  for(int i = 0; i< length(); i++)
  {
    if(_s[i]!=s._s[i]) return false;
  }
  return true;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
  if(length() != s.length()) return true;
  for(int i = 0; i< length(); i++)
  {
    if(_s[i]!=s._s[i]) return true;
  }
  return false;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
  if(_s[0] > s._s[0]) return false;
  for(int i = 0; i < length(); i++)
  {
    if(s._s[i] == '\0') return false;
    else if(_s[i] < s._s[i]) return true;
    else if(_s[i] < s._s[i]) return false;
  }
  return true;
}

// Return true if string "this" is greater than s
bool
MyString::operator > (const MyString &s)
{
  for(int i = 0; i < length(); i++)
  {
    if(s._s[i] == '\0') return true;
    else if(_s[i] < s._s[i]) return false;
    else if(_s[i] < s._s[i]) return true;
  }
  return false;
}

// Return character at position i.  Return '\0' if out of bounds.
char
MyString::operator [] (int i)
{
  if(i > length())
    return '\0';
  else return _s[i];
}

// Return C representation of string
const char *
MyString::cStr()
{
  // Add implementation here
  return _s;
}

// Get string length of this string.
int
MyString::length() const
{
  // Add implementation here
  return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
  // Add implementation here
  delete [] _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
  // Add implementation here

  // Allocate memory for the concatenated string
  MyString s = " ";
  s._s = new char[s1.length()+s2.length()+3];
  int i, j;
  for(i = 0; i < s1.length(); i++)
  {
    s._s[i] = s1._s[i];
  }
  // Add s1
  for(j = 0; j < s2.length(); j++)
  {
    s._s[i+j] = s2._s[j];
  }
 s._s[i+j] = '\0';
  // Add s2
  return s;
  
}

