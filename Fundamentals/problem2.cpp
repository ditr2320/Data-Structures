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

struct studentData
{
    string studentName; 
    int homework; 
    int recitation; 
    int quiz; 
    int exam; 
    double average; 
}; 

char calcLetter(double avg)
{
    char letter; 
    if(avg >= 90)
    {
        letter = 'A'; 
    }
    else if(avg >= 80 && avg <= 89.9)
    {
        letter = 'B'; 
    }
    else if(avg >= 70 && avg <= 79.9)
    {
        letter = 'C'; 
    }
    else if(avg >= 60 && avg <= 69.9)
    {
        letter = 'D'; 
    }
    else if(avg <60)
    {
        letter = 'F'; 
    }
    return letter; 
}


// length: Number of items in the array
void printList(const studentData students[], int length)
{
    for(int i = 0; i<length; i++)
    {
        cout << students[i].studentName << " earned " << students[i].average << " which is a(n) " << calcLetter(students[i].average) << endl; 
    }
}

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length)
{
    students[length].studentName = studentName; 
    students[length].homework = homework; 
    students[length].recitation = recitation; 
    students[length].quiz = quiz; 
    students[length].exam = exam; 
    students[length].average = (homework + recitation + quiz + exam)/4.0; 
}


int main(int argc, char* argv[])
{
    string studentName; 
    int homework; 
    int recitation; 
    int quiz; 
    int exam; 
    int length = 0;  
    studentData students[2000]; 

    ifstream file; 
    string line = ""; 
    string word; 
    string fileName = argv[1];  
    file.open(fileName);
    if(file.fail())
    {
        cout << "Failed to open the file." << endl; 
    }
    while(getline(file,line))
    {
        int counter = 0; 
        stringstream ss(line);
        while(getline(ss,word,','))
        {
            switch(counter)
            {
                case 0: studentName = word; 
                        break; 
                case 1: homework = stoi(word); 
                        break; 
                case 2: recitation = stoi(word); 
                        break; 
                case 3: quiz = stoi(word); 
                        break; 
                case 4: exam = stoi(word); 
                        break; 
            }  
            counter++; 
        } 
        addStudentData(students, studentName, homework, recitation, quiz, exam, length); 
        length++;
    }
    printList(students,length);
    //writing output file
    string outFileName = argv[2];  
    char lowB= argv[3][0];  
    char upperB = argv[4][0];   
    ofstream out_file; 
    out_file.open(outFileName); 
    if(out_file.is_open())
    {
        for(int i = 0; i< length; i++)
        {
            char letter = calcLetter(students[i].average); 
            if(letter <= lowB && letter >= upperB)
            {
                out_file << students[i].studentName << "," << students[i].average << "," << letter << endl;  
            }
        }
    }
    out_file.close(); 
    return 0; 
}
