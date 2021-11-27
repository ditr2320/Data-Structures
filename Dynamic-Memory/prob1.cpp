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
#include <stdio.h>
using namespace std; 

struct wordRecord
{
    string word; 
    int count; 
}; 

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[])
{
    ifstream file; 
    string line = ""; 
    file.open(ignoreWordFileName);
    int counter = 0; 
    if(file.fail())
    {
        cout << "Failed to open ignore words file." << endl; 
    }
    while(getline(file,line))
    {
        ignoreWords[counter] = line; 
        counter++; 
    }
}

bool isIgnoreWord(string word, string ignoreWords[])
{
    bool isIgnoreWord = 0;
    for(int i = 0; i< 50; i++)
    {
        if(ignoreWords[i] == word)
        {
            isIgnoreWord = 1; 
            return isIgnoreWord; 
        }
    }
    return isIgnoreWord; 
}

bool isRepeat(string word, wordRecord distinctWords[], int length)
{
    bool isRepeat = 0; 
    for(int i = 0; i< length; i++)
    {
        if(distinctWords[i].word == word)
        {
            isRepeat = 1; 
            return isRepeat;    
        }
    }
    return isRepeat;     
}

int findIndex(string word, wordRecord distinctWords[], int length)
{
    int indexNum = 0; 
    for(int i = 0; i<length; i++)
    {
        if(distinctWords[i].word == word)
        {
            indexNum = i; 
            return indexNum; 
        }
    }
    return indexNum; 
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length)
{
   int wordCount = 0; 
   for(int i = 0; i< length;i++)
   {
       wordCount = wordCount + distinctWords[i].count; 
   }
   return wordCount; 
}

void sortArray(wordRecord distinctWords[], int length)
{
    wordRecord mArray[length]; 
    int newValue = distinctWords[0].count; 
    for(int i = 0; i< length; i++)
    {
        for(int j = 0; j<length; j++)
        {
            if(distinctWords[i].count == distinctWords[j].count)
            {
                if(distinctWords[i].word[0] < distinctWords[j].word[0])
                {
                    wordRecord temp = distinctWords[j]; 
                    distinctWords[j] = distinctWords[i]; 
                    distinctWords[i] = temp;
                }
            }
            if(distinctWords[i].count > distinctWords[j].count)
            {
                wordRecord temp = distinctWords[j]; 
                distinctWords[j] = distinctWords[i]; 
                distinctWords[i] = temp;
            } 
        }
    }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords)
{
    float prob = 0; 
    cout<<setprecision(5)<<fixed; 
    for(int i = N; i < (N+10); i++)
    {
        prob = (float) distinctWords[i].count / totalNumWords; 
        cout << prob << " - " << distinctWords[i].word << endl;
    }
}

int main(int argc, char* argv[])
{
    string ignoreWords[50]; 
    int length = 100;  
    wordRecord *distinctWords = new wordRecord[length]; 
    int N = stoi(argv[1]); 
    getIgnoreWords(argv[3],ignoreWords); 
    ifstream file1; 
    string word = ""; 
    file1.open(argv[2]);
    int index = 0; 
    int indexNum = 0; 
    int timesDoubled = 0; 
    if(file1.fail())
    {
        cout << "Failed to open ignore words file." << endl; 
    }
    while (file1 >> word)
    {
        if(isIgnoreWord(word, ignoreWords) == 0) 
        {
            if(isRepeat(word, distinctWords, length) == 0) //first time encountering word
            {
                distinctWords[index].word = word; 
                index++; 
            }
            if(isRepeat(word, distinctWords, length) == 1) // word encountered previously 
            {
                indexNum = findIndex(word, distinctWords, index); 
                distinctWords[indexNum].count ++;
            }
        }
        if(index == length)
        {
            length = length*2; 
            timesDoubled++; 
            wordRecord *temp = new wordRecord[(length)]; 
            for(int i = 0; i<(length/2); i++)
            {
                temp[i] = distinctWords[i]; 
            }
            delete[] distinctWords; 
            distinctWords = temp; 
        }
    }
    sortArray(distinctWords,index); 
    cout << "Array doubled: " << timesDoubled << endl; 
    cout << "Distinct non-common words: " << index << endl; 
    cout << "Total non-common words: " << getTotalNumberNonIgnoreWords(distinctWords, index) << endl; 
    cout << "Probability of next 10 words from rank " << argv[1] << endl; 
    cout << "---------------------------------------" << endl; 
    printTenFromN(distinctWords, N , getTotalNumberNonIgnoreWords(distinctWords, index)); 
    return 0; 
}