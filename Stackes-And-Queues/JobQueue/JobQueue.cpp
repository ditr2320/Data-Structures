#include "JobQueue.hpp"

#include <iostream>
#include <string>
using namespace std; 
JobQueue::JobQueue()
{
    queueFront = 0; 
    queueEnd = 0; 
    counter = 0; 
}

bool JobQueue::isEmpty()
{
    if(counter == 0) return true; 
    else return false; 
}

bool JobQueue::isFull()
{
    if(counter == SIZE) return true; 
    else return false; 
}

void JobQueue::enqueue(string mystr)
{
    if(isEmpty())
    {
        queue[0] = mystr; 
        queueEnd = 1; 
        counter++; 
        return; 
    }
    if(isFull())
    {
        cout << "Queue full, cannot add new job" << endl; 
        return; 
    }
    if(queueEnd == SIZE)
    {
        queueEnd = 0; 
        queue[queueEnd] = mystr; 
        queueEnd++; 
        counter++; 
        return; 
    }
    queue[queueEnd] = mystr; 
    queueEnd++; 
    counter++; 
    return; 
}

void JobQueue::dequeue()
{
    if(isEmpty())
    {
        cout << "Queue empty, cannot dequeue a job" << endl; 
        return; 
    }
    if(queueFront == SIZE - 1)
    {
        queueFront = 0; 
        counter--; 
        return; 
    }
    queueFront++; 
    counter--; 
}

string JobQueue::peek()
{
    if(isEmpty())
    {
        cout << "Queue empty, cannot peek" << endl; 
        return ""; 
    }
    string myS = queue[queueFront]; 
    return myS; 
}

int JobQueue::queueSize()
{
    return counter; 
}