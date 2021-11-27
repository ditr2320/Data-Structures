#include "miniGit.hpp"
#include <iostream>
#include <fstream>
#include <filesystem> 
#include <vector>
using namespace std; 

namespace fs = std::filesystem; 

MiniGit::MiniGit()
{
    // creating .miniGit directory
    fs::remove_all(".miniGit"); 
    fs::create_directory(".miniGit"); 

    // creating doubly linked list

    H->commitNumber = 0; 
    H->head = NULL; 
    H->next = NULL; 
    H->previous = NULL; 
}

MiniGit::~MiniGit()
{
    fs::remove_all(".miniGit"); 
}


doublyNode* MiniGit::lastDLLnode()
{
    doublyNode* curr = H; 
    while(curr->next != NULL)
    {
        curr = curr->next; 
    }
    return curr; 
}

doublyNode* MiniGit::searchDLLnode(int commitNum)
{
    doublyNode* curr = H; 
    while(curr !=0)
    {
        if(curr -> commitNumber == commitNum) return curr; 
        else curr = curr -> next; 
    }
    return curr; 
}

bool MiniGit::fileAdded(string fileName) //traverse SLL
{
    doublyNode* D = lastDLLnode(); 
    bool fileAdded = false; 
    singlyNode* curr = D->head; 
    while(curr != NULL)
    {
        if(curr->fileName == fileName)
        {
            fileAdded = true; 
        }
        curr = curr-> next; 
    }
    return fileAdded;
}


void MiniGit::addSLLnode(string filename)
{
    doublyNode* D = lastDLLnode(); 
    singlyNode* prev = D->head; 
    //creating node to insert 
    singlyNode* tmp = new(singlyNode); 
    tmp -> fileName = filename; 
    tmp -> next = NULL; 
    tmp -> fileNum = 0;  
    tmp -> fileVersion = filename + "_" + to_string(tmp->fileNum); //FIX LATER

    if(prev == NULL)
    {
        //inserting as first node
        tmp -> next = D->head; 
        D->head = tmp; 
        cout << "************************************************" << endl;
        cout << "adding: " << filename << " (HEAD)" << endl; 
        return; 
    }
    
    while(prev->next != NULL)
    {
        prev = prev->next; 
    }

    tmp -> next = prev -> next; 
    prev -> next = tmp; 
    cout << "************************************************" << endl;
    cout << "adding: " << tmp ->fileVersion << endl; 

}

void MiniGit::printSLL()
{
    doublyNode* D = lastDLLnode(); 
    singlyNode* curr = D->head;
    cout << "************************************************" << endl;
    if(curr == NULL)
    {
        cout << "Singly linked list is empty" << endl; 
        return; 
    }
    cout << "Current List: "; 
    while(curr !=0)
    {
        cout << curr->fileName << "(" << curr->fileVersion << ")" << " -> "; 
        curr = curr -> next; 
    }
    cout << "NULL" << endl; 
    return; 
}

singlyNode* MiniGit::searchSLLnode(string filename)
{
    doublyNode* D = lastDLLnode(); 
    singlyNode* curr = D->head; 
    while(curr != NULL)
    {
        if(curr -> fileName == filename) return curr; 
        else curr = curr -> next; 
    }
    return 0; 
}

void MiniGit::deleteSLLnode(string filename)
{
    doublyNode* D = lastDLLnode(); 
    singlyNode* tmp = new singlyNode; 
    tmp = searchSLLnode(filename); 
    if(tmp == 0)
    {
        cout << "Filename does not exist in SLL." << endl; 
        return; 
    }
    singlyNode* curr = D->head; 
    singlyNode* prev = 0; 
    while(curr -> next != NULL)
    {
        if(curr == tmp) break; 
        else
        {
            prev = curr; 
            curr = curr -> next; 
        }
    }
    if(prev == 0) // first node deleted 
    {
        cout << "************************************************" << endl;
        cout << "Deleting: " << curr->fileName << "(" << curr->fileVersion << ")" << endl;
        D->head = curr -> next; 
        delete curr; 
    }
    else //intermediate node deleted
    {
        cout << "************************************************" << endl;
        cout << "Deleting: " << curr->fileName << "(" << curr->fileVersion << ")" << endl; 
        prev-> next = curr -> next; 
        delete curr; 
    }
}

//helper function 
bool fileExists(string directory, string filename)
{
    ifstream file; 
    string str = (directory + "/" + filename); 
    cout << str << ": "; 
    file.open(str); 
    if(file.fail() == true)
    {
        return false; 
    }
    file.close(); 
    return true; 
}

void copyFile(string filename1, string filename2)
{
    //filename1 = original file name
    //filename2 = repository file name 
    ifstream file; 
    string line = ""; 
    vector <string> lines; 
    int counter = 0; 
    file.open(filename1); 
    while(getline(file,line))
    {
        lines.push_back(line); 
        counter++; 
    }
    ofstream out_file; 
    //The newly copied file should get the name from the node’s fileVersion member.
    out_file.open(".miniGit/" + filename2); 
    for(int i = 0; i < counter; i++)
    {
        out_file << lines.at(i) << endl; 
    }
    return; 
}

bool compareFiles(string filename1, string filename2)
{
    ifstream file1; 
    ifstream file2; 
    file1.open(filename1); 
    file2.open(".miniGit/" + filename2); 
    string line1 = ""; 
    string line2 = "";
    vector <string> lines1; 
    vector <string> lines2;
    while(getline(file1,line1))
    {
        lines1.push_back(line1); 
    }
    while(getline(file2,line2))
    {
        lines2.push_back(line2); 
    }
    if(lines1 == lines2)
    {
        return true; 
    }
    else
    {
        return false; 
    }

}

singlyNode* deepCopy(singlyNode*&copy)
{
	singlyNode* result = new singlyNode (*copy),
	*iterator = result;
	for (singlyNode* it = copy->next; it != NULL; it = it->next)
	{
		iterator->next = new singlyNode (*it);
		iterator = iterator->next;
	}
	iterator->next = NULL;
	return result;
}

doublyNode* MiniGit::addDLLnode()
{
    //find last DLL node 
    doublyNode* crawler = lastDLLnode(); 
    //add new node
    doublyNode* curr = new(doublyNode); 
    singlyNode* copy = deepCopy(crawler->head); 
    curr -> previous = crawler; 
    curr -> head = copy; 
    curr -> next = NULL; 
    curr -> commitNumber = (curr->previous->commitNumber +1); 
    crawler -> next = curr; 
    return curr; 
}

bool MiniGit::commit()
{
    bool changed= false; 
    // traverse every node in current SLL and do the following: 
    doublyNode* D = lastDLLnode(); 
    singlyNode* tmp = D->head; 
    bool fileExist; 
    bool fileSame; 
    while(tmp != NULL)
    {
        //check whether corresponding fileVersion file exists in .miniGit directory
        fileExist = fileExists(".miniGit",tmp->fileVersion); 
        if(fileExist == false)
        {
            //if it does not exist - copy the file from current directory into the .miniGit directory
            //The newly copied file should get the name from the node’s fileVersion member.
            copyFile(tmp ->fileName, tmp->fileVersion); 
            cout << "Copying to repository" << endl; 
            // temp -> fileNum++; 
            // temp -> fileVersion = (temp->fileName + "_" + to_string(temp->fileNum)); 
            changed = true; 
        }
        if(fileExist == true)
        {
            //if the file does exist in .miniGit -  check whether the current directory file has been changed with respect to the fileVersion file.
            fileSame = compareFiles(tmp ->fileName, tmp->fileVersion); 
            if(fileSame == true)
            {
                // if unchanged - do nothing
                cout << "files are the same" << endl; 
            }
            if(fileSame == false)
            {
                // if changed - copy the file from the current directory to the .miniGit directory
                // give it a name with the incremented version number
                // update the SLL node member fileversion to the incremented name

                //copyFile(tmp ->fileName, tmp->fileVersion); 
                cout << "Copying to repository" << endl; 
                tmp -> fileNum++; 
                tmp -> fileVersion = (tmp->fileName + "_" + to_string(tmp->fileNum)); 
                copyFile(tmp->fileName, tmp->fileVersion);  
                changed = true; 
            }
        }
        tmp = tmp-> next; 
    }
    return changed; 
}



void MiniGit::printDLL()
{
    doublyNode* curr = H; 
    if(H == NULL)
    {
        cout << "************************************************" << endl;
        cout << "Doubly linked list is empty" << endl; 
        cout << "************************************************" << endl;
        return; 
    }
    cout << "Current List: "; 
    cout << "HEAD -> "; 
    while(curr !=0)
    {
        if(curr -> commitNumber >= 0)
        {
        cout << curr->commitNumber <<  " -> "; 
        }
        curr = curr -> next; 
    }
    cout << "NULL" << endl; 
    cout << "************************************************" << endl;
    return; 
}

void checkoutFile(string filename1, string filename2)
{
    //writing from old commit
    ifstream file; 
    string line = ""; 
    vector <string> lines; 
    int counter = 0; 
    file.open(".miniGit/" + filename1); 
    while(getline(file,line))
    {
        lines.push_back(line); 
        counter++; 
    }
    ofstream out_file; 
    //writing to original file
    out_file.open(filename2); 
    for(int i = 0; i < counter; i++)
    {
        out_file << lines.at(i) << endl; 
    }
    return; 
}


void MiniGit::checkout(int commitNum)
{
    if(commitNum < 0) 
    {
        cout << "Enter a number greater than 0" << endl; 
        return; 
    }
    doublyNode* curr = searchDLLnode(commitNum); 

    cout << "testing commit number: " << curr ->commitNumber << endl; 
    cout << "testing version:" << curr -> head -> fileVersion << endl; 
    
    checkoutFile(curr->head->fileVersion, curr->head->fileName);
    while(curr->head->next!=NULL)
    {
        cout << "testing version:" << curr -> head -> fileVersion << endl; 
        curr->head = curr->head-> next;
        checkoutFile(curr->head->fileVersion, curr->head->fileName);  
    }
    return; 
}

void MiniGit::printSLLinfo(int commitNum)
{

    if(commitNum < 0) 
    {
        cout << "Enter a number greater than 0" << endl; 
        return; 
    }
    doublyNode* temp = searchDLLnode(commitNum); 
    singlyNode* curr = temp->head; 
    cout << "Commit number from DLL: " << temp->commitNumber << endl; 

    if(curr == NULL)
    {
        cout << "************************************************" << endl;
        cout << "Singly linked list is empty" << endl; 
        cout << "************************************************" << endl;
        return; 
    }
    cout << "Current List: "; 
    while(curr != NULL)
    {
        cout << curr->fileName << "(" << curr->fileVersion << ")" << "(" << curr->fileNum << ")"" -> "; 
        curr = curr -> next; 
    }
    cout << "NULL" << endl; 
    cout << "************************************************" << endl;
    return; 
}

