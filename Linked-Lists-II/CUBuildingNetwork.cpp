/*******************************************************************/
/*                CUBuildingNetwork Implementation                 */
/*******************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*       This class uses a linked-list of CUBuilding nodes to      */
/*       represent communication paths between buildings           */
/*******************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() 
{
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the CUBuilding *previous and the CUBuilding that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int totalRoom) 
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding* tmp = new CUBuilding; 
    tmp -> name = buildingName; 
    tmp -> totalRoom = totalRoom; 

    if(previous == 0) // inserting as the first node 
    {
        tmp -> next = head; 
        head = tmp; 
        cout << "adding: " << buildingName << " (HEAD)" << endl; 
    }
    else
    {
        tmp -> next = previous -> next; 
        previous -> next = tmp; 
        cout << "adding: " << buildingName << " (prev: " << previous -> name << ")" << endl; 
    }

}

/*
 * Purpose: populates the network with the predetermined CUBuildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    // TODO: Copy-paste your solution from Assignment 3
    // MODIFICATION: Use deleteEntireNetwork function before adding buildings
    string nameArr[] = {"FLMG","DLC", "ECOT", "CASE", "AERO", "RGNT"}; 
    int numArr[] = {2,10,6,5,4,9}; 
    for (int i = 0; i<6; i++)
    {
        CUBuilding* curr = new CUBuilding;
        CUBuilding* prev = new CUBuilding; 
        curr -> totalRoom = numArr[i];  
        curr -> name = nameArr[i]; 
        curr -> next = 0; 
        if(i == 0)
        {
            prev = NULL; 
            curr -> next = head; 
            head = curr; 
            cout << "adding: " << nameArr[i] << " (HEAD)" << endl; 
        }
        else
        {
            prev = searchForBuilding(nameArr[i-1]); 
            curr-> next = prev -> next; 
            prev -> next = curr; 
            cout << "adding: " << nameArr[i] << " (prev: " << prev -> name << ")" << endl; 
        }
    }

}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding* curr = head; 
    while(curr != NULL)
    {
        if(curr -> name == buildingName) return curr; 
        else curr = curr -> next; 
    }
    return 0; 

}

/*
 * Purpose: Relay a message through the linked list until the specified CUBuilding
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding* curr = head; 
    CUBuilding* tmp = head; 
    tmp = searchForBuilding(receiver); 
    if(head == NULL)
    {
        cout << "Empty list" << endl; 
        return; 
    }
    else if(tmp == 0)
    {
        cout << "Building not found" << endl; 
        return; 
    }
    else
    {
        while(curr -> name != receiver) 
        {
            curr -> numberMessages ++; 
            cout << curr -> name << " [# messages received: " << curr -> numberMessages << "] received: "; 
            cout << curr -> message << "available room at " << curr -> name << " is " << curr -> totalRoom << endl ;
            curr = curr -> next; 
        }       
        curr -> numberMessages ++; 
        cout << curr -> name << " [# messages received: " << curr -> numberMessages << "] received: "; 
        cout << curr -> message << "available room at " << curr -> name << " is " << curr -> totalRoom << endl ;
        curr = curr -> next; 
    }

}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() 
{
    // TODO: Copy-paste your solution from Assignment 3
    CUBuilding* curr = head; 
    cout << "== CURRENT PATH ==" << endl; 
    if(head == NULL)
    {
        cout << "nothing in path" << endl; 
        cout << "===" << endl; 
        return; 
    }
    while(curr !=0)
    {
        cout << curr -> name << "(" << curr -> totalRoom << ") -> "; 
        curr = curr -> next; 
    }
    cout << "NULL" << endl; 
    cout << "===" << endl; 
    return; 

}

/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/

/*
 * Purpose: Delete the CUBuilding in the network with the specified name.
 * @param buildingName name of the CUBuilding to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) 
{
    // TODO: Complete this function
    CUBuilding* tmp = new CUBuilding; 
    tmp = searchForBuilding(buildingName); 
    if(tmp == 0)
    {
        cout << "Building does not exist." << endl; 
        return; 
    }
    CUBuilding* curr = head; 
    CUBuilding* prev = 0; 
    while(curr !=0)
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
        head = curr -> next; 
        delete curr; 
    }
    else //intermediate node deleted
    {
        prev-> next = curr -> next; 
        delete curr; 
    }
}

/*
 * Purpose: deletes all CUBuildings in the network starting at the head CUBuilding.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    // TODO: Complete this function
    CUBuilding* tmp = head; 
    while(head != NULL)
    {
        tmp = head; 
        head = head -> next; 
        cout << "deleting: " << tmp -> name << endl; 
        delete tmp; 
    }
    cout << "Deleted network" << endl; 

}

/*
* Purpose: Creates a loop from last node to the CUBuilding specified.
* @param buildingName name of the CUBuilding to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) 
{
    // TODO: Complete this function
    CUBuilding* tmp = new CUBuilding; 
    CUBuilding* curr = head; 
    CUBuilding* prev = 0; 
    tmp = searchForBuilding(buildingName); 
    while(curr -> next != 0)
    {
        curr = curr -> next;        
    }
    if(tmp == 0) // Building does not exist
    {
        return curr; 
    }
    else
    {
        curr -> next = tmp; 
    }
    return curr; 
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool CUBuildingNetwork::detectLoop() 
{
    // TODO: Complete this function
    if(head == NULL) return false; 
    CUBuilding* fast = head;  
    CUBuilding* slow = head; 
    while(fast != NULL && slow != NULL)
    {
        fast = fast -> next -> next; 
        slow = slow -> next; 
        if(fast == slow) return true; 
    }
    return false; 
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk to the end of the List
 * @param: start_index, end_index
 * @return: none
 */
void CUBuildingNetwork::readjustNetwork(int start_index, int end_index)
{
    // TODO: Complete this function
    if(head == NULL) 
    {
        cout << "Linked List is Empty" << endl; 
        return; 
    }
    int counter = 0; // keeps track of index of final node 
    CUBuilding* prev = head; 
    CUBuilding* first = head;  
    CUBuilding* second = head; 
    CUBuilding* last = head; 

    while(last-> next != NULL) // finding the final node 
    {
        last = last -> next;
        counter ++;  // index of node 
    }
    if(end_index >= counter || end_index < 0 )
    {
        cout << "Invalid end index" << endl; 
        return; 
    }
    if(start_index >= counter || end_index < 0)
    {
        cout << "Invalid start index" << endl; 
        return; 
    }
    if(start_index > end_index)
    {
        cout << "Invalid indices" << endl;
        return; 
    }
    for(int i = 0; i < start_index; i++) // finding first index node
    {
        prev = first; 
        first = first -> next;
    }
    for(int i = 0; i < end_index; i++) // finding second index node 
    {
        second = second -> next; 
    }
    if(start_index == 0)
    {
        last -> next = head; 
        head = second -> next; 
        second -> next = NULL; 
        return; 
    }

    last -> next = first; 
    prev -> next = second -> next; 
    second -> next = NULL; 
    
}

/*
 * Purpose: Destructor to delete the entire list on program termination
 * @param none
 * @return none
 */
CUBuildingNetwork::~CUBuildingNetwork()
{
    // TODO: Complete this function

}
