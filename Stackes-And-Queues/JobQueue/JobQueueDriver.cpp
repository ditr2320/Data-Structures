/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
#include <string> 
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	JobQueue jq;  
	/* TODO */
	string choice; 
	string numJobs; 
	string numJobs1;
	string job; 
	int size;   
	while(choice != "3")
	{
		menu(); 
		getline(cin, choice); 
		switch(choice[0])
		{
			case '1':cout << "Enter the number of jobs to be created:"<< endl; 
					getline(cin, numJobs); 
					for(int i = 1; i <= stoi(numJobs); i++)
					{
						cout << "job" << i << ":" << endl;
						getline(cin, job); 
						jq.enqueue(job); 
					}
					break; 
			case '2':cout << "Enter the number of jobs to be dispatched:" << endl; 
					getline(cin, numJobs1); 
					size = jq.queueSize(); 
					if(stoi(numJobs1) > size)
					{
						for(int i = 0; i < size; i++)
						{
							cout << "Dispatched: " << jq.peek() << endl; 
							jq.dequeue(); 
						}
						cout << "No more jobs to be dispatched from queue" << endl; 
					}
					else
					{
						for(int i = 0; i< stoi(numJobs1); i++)
						{
							cout << "Dispatched: " << jq.peek() << endl;
							jq.dequeue(); 
						}
					}
					break; 	
			case '3': cout << "Number of jobs in the queue:" << jq.queueSize() << endl; 
					break;
			default: break;
		}
	}
}
