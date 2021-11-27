#include <iostream>
#include <fstream>
#include <filesystem> 
using namespace std; 

#ifndef MINIGIT_HPP
#define MINIGIT_HPP

struct singlyNode{
    std::string fileName; // Name of local file
    std::string fileVersion; // Name of file in .minigit folder 
    singlyNode * next;
    int fileNum; 
}; 

struct doublyNode{
    int commitNumber;
    int numCommits; 
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
}; 

class MiniGit
{
    private: 
    doublyNode* H; 

    public: 
    MiniGit(); 
    ~MiniGit(); 

    bool fileAdded(string fileName); 
    void addSLLnode(string filename); 
    singlyNode* searchSLLnode(string filename); 
    void deleteSLLnode(string filename); 

    bool commit(); 
    void checkout(int commitNum); 

    void printSLL(); 
    void printDLL(); 
    void printSLLinfo(int commitNum); 

    doublyNode* lastDLLnode(); 
    doublyNode* searchDLLnode(int commitNum); 
    doublyNode* addDLLnode(); 
    singlyNode* getCopy(); 
}; 

#endif