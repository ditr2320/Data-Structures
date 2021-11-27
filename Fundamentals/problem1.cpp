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
#include <cmath>

using namespace std; 

int addToArrayAsc(float sortedArray[], int numElements, float newValue)
{
    if(numElements == 0)
    {
        sortedArray[0] = newValue; 
        numElements++; 
        return numElements; 
    }
    if(numElements < 100)
    {
        float mArray[100]; 
        for(int i = 0; i<numElements; i++)
        {
            mArray[i] = sortedArray[i]; 
        }
        for(int i = 0; i< numElements; i++)
        {
            if(newValue <= sortedArray[i])
            {
                sortedArray[i] = newValue; 
                for(int j = i+1; j<numElements+1; j++)
                {
                    sortedArray[j] = mArray[j-1]; 
                }
                numElements++; 
                return numElements; 
            }
            if(i == numElements-1)
            {
                sortedArray[i+1] = newValue; 
                numElements++; 
                return numElements; 
            }
        }
    }
    return numElements; 
}


int main(int argc, char* argv[])
{
    float myArr[100]; 
    ifstream file; 
    string line = ""; 
    string fileName = argv[argc-1]; 
    float number; 
    int numElements = 0; 
    file.open(fileName);
    if(file.fail())
    {
        cout << "Failed to open the file." << endl; 
    }
    while(getline(file,line))
    {
        if(line.length()>0)
        {
            number = stof(line); 
            numElements = addToArrayAsc(myArr, numElements, number); 
        }
        for(int i = 0; i<numElements; i++)
        {
            cout << myArr[i]; 
            if(i < numElements-1)
            {
                cout << ","; 
            }
        }
        cout << endl; 
    }
    cout << endl; 
    return 0; 

}
