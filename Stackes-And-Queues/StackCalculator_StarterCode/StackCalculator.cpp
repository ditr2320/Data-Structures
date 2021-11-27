#include <iostream>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  //TODO:
  stackHead = NULL; 
}

StackCalculator::~StackCalculator()
{
  //TODO:
  Operand* temp; 
  while(stackHead != NULL)
  {
    temp = stackHead -> next; 
    delete stackHead; 
    stackHead = temp; 
  }
}

bool StackCalculator::isEmpty()
{
	if(stackHead == NULL)
  {
    return true; 
  }
  return false; 
}

void StackCalculator::push(float number)
{
  //TODO:
  Operand* newNode = new Operand; 
  newNode -> number = number; 
  newNode -> next = stackHead; 
  stackHead = newNode; 
}

void StackCalculator::pop()
{
	//TODO:
  if(isEmpty() == true) 
  {
    cout << "Stack empty, cannot pop an item." << endl; 
    return; 
  }
  Operand* temp = stackHead;
  stackHead = stackHead -> next;
  delete temp; 
}

Operand* StackCalculator::peek()
{
	//TODO:
  if(isEmpty() == true)
  {
    cout << "Stack empty, cannot peek." << endl; 
    return nullptr; 
  }
  else
  {
    Operand* top = stackHead; 
    return top; 
  }
  return nullptr;// remove this line if you want
}

bool StackCalculator:: evaluate(string* s, int size)
{
  for(int i = size-1; i>=0; i--)
  {
    float newNum = 0.0; 
    if(isNumber(s[i]) == true)
    {
      push(stof(s[i]));
    }
    else if(s[i] == "*")
    {
      if(stackHead == NULL || stackHead -> next == NULL) //bc need at least two operands 
      {
        cout << "err: not enough operands" << endl; 
        return false; 
      }
      newNum = stackHead -> number * stackHead -> next -> number; 
      pop(); 
      pop(); 
      push(newNum); 
    }
    else if(s[i] == "+")
    {
      if(stackHead == NULL || stackHead -> next == NULL) //bc need at least two operands 
      {
        cout << "err: not enough operands" << endl; 
        return false; 
      }
      newNum = stackHead -> number + stackHead -> next -> number; 
      pop(); 
      pop(); 
      push(newNum); 
    }
    else
    {
      cout << "err: invalid operation" << endl; 
      return false; 
    }
  }
	return true;
}
