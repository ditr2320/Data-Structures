#include <iostream>
#include <fstream>
#include <filesystem> 
#include "miniGit.hpp"
using namespace std; 

void menuOptions(MiniGit& M)
{
    // menu options
    M.printDLL(); 
    int choice = 0; 
    string filename = "";
    ifstream file; 
    bool fileadded; 
    bool committed; 
    int commitNum;   

    while(choice != 6)
    {
        cout << "Select a numerical option" << endl; 
        cout << "====== Main Menu ======" << endl; 
        cout << "1. add" << endl;   
        cout << "2. remove" << endl; 
        cout << "3. commit" << endl; 
        cout << "4. checkout" << endl; 
        cout << "5. print commit info" << endl; 
        cout << "6. quit" << endl; 
        cin >> choice; 
        switch(choice)
        {
            case 1: cout << "Please enter file name" << endl;  
                    cin >> filename; 
                    file.open(filename); 
                    // check if file exists 
                    if(file.fail() == true) 
                    {
                        cout << "************************************************" << endl;
                        cout << "file does not exist" << endl; 
                        cout << "************************************************" << endl;
                        file.close();
                        break; 
                    }
                    // check if file as already been added
                    fileadded = M.fileAdded(filename); 
                    if(fileadded == true)
                    {
                        cout << "************************************************" << endl;
                        cout << "file has already been added" << endl; 
                        cout << "************************************************" << endl;
                        file.close();
                        break; 
                    }
                    file.close(); 
                    // new SLL node gets added containing name of input file, name of respository file, and pointer to next node 
                    // repository file is combo of original file name and the version number 
                    M.addSLLnode(filename);  
                    break; 
            case 2: cout << "Please enter file name" << endl; 
                    cin >> filename; 
                    // check if SLL node exists in the current version of the respository 
                    fileadded = M.fileAdded(filename); 
                    if(fileadded == false)
                    {
                        cout << "file has not been added" << endl; 
                        break; 
                    }
                    // if found, delete the SLL node
                    M.deleteSLLnode(filename); 
                    break; 
            case 3: cout << "************************************************" << endl;
                    cout << "Committing changes" << endl; 
                    cout << "************************************************" << endl;
                    committed = M.commit(); 
                    if(committed == true)
                    {
                        M.addDLLnode(); 
                    }
                    cout << endl; 
                    break; 
            case 4: cout << "Please enter a commit number" << endl; 
                    cin >> commitNum; 
                    M.checkout(commitNum); 
                    // if commit number is valid, replace files in the current directory with those from .miniGit
                    break; 
            case 5: M.printDLL(); 
                    cout << "Please enter a commit number" << endl; 
                    cin >> commitNum; 
                    M.printSLLinfo(commitNum); 
            case 6: break; 
            default:cout << "Error, please enter a number between 1 and 6" << endl; 
                    break; 
        }
    }
}

/*Also note that you must disallow add, remove, and commit operations
 when the current version is different from the most recent commit (the last DLL node). */

int main()
{
    cout << "Would you like to initialize a new repository?" << endl; 
    cout << "(1) Yes (2) No" << endl; 
    int choice; 
    cin >> choice; 
    if(choice == 1) //init 
    {
        MiniGit M = MiniGit(); 
        cout << "************************************************" << endl;
        cout << "New repository has been initialized" << endl;
        cout << "************************************************" << endl;
        menuOptions(M); 
    }
    else
    {
        return 0; 
    }
    return 0; 
}
