//CSCI 2270 Spring 2021
//Author: Didi Trifonova
// 
 
#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std; 

bool append(string* &str_arr, string s, int &numEntries, int &arraySize)
{
    bool isDoubled = false; 
    if(numEntries < arraySize )
    {
        str_arr[numEntries] = s; 
        numEntries ++; 
    }
    else 
    {
        arraySize = arraySize*2; 
        string *temp = new string[(arraySize)]; 
        for(int i = 0; i<(arraySize/2); i++)
        {
            temp[i] = str_arr[i]; 
        }
        delete[] str_arr; 
        str_arr = temp; 
        isDoubled = true; 
        str_arr[numEntries] = s; 
        numEntries ++; 
    }
    return isDoubled; 
}

int main()
{
    
    return 0; 
}