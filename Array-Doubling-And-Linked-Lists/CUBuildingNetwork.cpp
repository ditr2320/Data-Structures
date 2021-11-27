/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/
  
#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
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
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {

    CUBuilding* tmp = new CUBuilding; 
    tmp -> name = buildingName; 
    tmp -> totalRoom = numOfroom; 

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
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */

void CUBuildingNetwork::loadDefaultSetup()
{
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
    CUBuilding* curr = head; 
    while(curr != NULL)
    {
        if(curr -> name == buildingName) return curr; 
        else curr = curr -> next; 
    }
    return 0; 
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver) 
{
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
void CUBuildingNetwork::printNetwork() {
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
