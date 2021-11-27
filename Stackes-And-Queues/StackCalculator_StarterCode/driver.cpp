#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"

using namespace std;

bool isNumber2(string s)
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

int main()
{
  // stack to hold the operands
  StackCalculator stack;

  int numElement = 0;
  string* inparr = new string[50];

  // enter a number
  string number;
  cout << "Enter the operators and operands ('+', '*') in a prefix format" << endl;

    /* TODO
       1. Read input (operators and operands) until you encounter a "="
       2. store them in inparr
    */

  while(number != "=")
  {
    cout << "#> ";
    getline(cin, number);
    bool Num = isNumber2(number); 
    // if(Num == false && number != "*" && number!= "+" && number!= "=")
    // {
    //   cout << "Invalid expression" << endl; 
    // }
    // else
    // {
    //   if(number != "=")
    //   {
    //   inparr[numElement] = number; 
    //   numElement++; 
    //   }
    // }
      if(number != "=")
      {
      inparr[numElement] = number; 
      numElement++; 
      }
  }

  /* TODO - If the inparr is empty then print "No operands: Nothing to evaluate"
            else call the evaluate function
  */
  bool validate = false; 
  if(numElement == 0)
  {
    cout << "No operands: Nothing to evaluate" << endl; 
  }
  else
  {
    validate = stack.evaluate(inparr, numElement); 
  }

  /* TODO - Validate the expression
      1. If valid then print the result cout << "Result= "<<result << endl;
      2. Else, print "Invalid expression"*/
  if(validate == true)
  {
    cout << "Result= " << stack.getStackHead() -> number << endl; 
  }
  else
  {
    //cout << "Invalid expression" << endl; 
  }

  return 0;
}
