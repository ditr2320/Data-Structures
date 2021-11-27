#include "Graph.hpp"
#include <iostream> 
#include <vector>
#include <queue>
#include <stack>
using namespace std; 

void Graph::addVertex(std::string name)
{
    vertex* v = new vertex; 
    v->name = name; 
    v->visited = false; 
    vertices.push_back(v); 
}

void Graph::addEdge(std::string v1, std::string v2)
{
    vertex* u1; 
    vertex* u2; 
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == v1)
        {
            u1 = vertices[i]; 
        }
        if(vertices[i]->name == v2)
        {
            u2 = vertices[i]; 
        }
    }
    adjVertex U1; 
    adjVertex U2; 
    U1.v = u1; 
    U2.v = u2; 
    u1->adj.push_back(U2); 
    u2->adj.push_back(U1); 
}

void Graph::displayEdges()
{
    // Your code here
    for(int i = 0; i<vertices.size(); i++)
    {
        cout << vertices[i]->name << " --> "; 
        for(int j = 0; j<vertices[i]->adj.size(); j++) 
        {
            cout<< vertices[i]->adj[j].v->name << " "; 
        }
        cout << endl; 
    }
}

void Graph::breadthFirstTraverse(string sourceVertex)
{
    for(int i = 0; i<vertices.size(); i++)
    {
        vertices[i]->visited = false; 
    }
    vertex* vStart;
    for(int i = 0; i<vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex)
        {
            vStart = vertices[i]; 
        }
    }
    vStart -> distance = 0; 
    vStart -> visited = true; 
    vertex* n; 
    queue<vertex*> q; 
    q.push(vStart); 
    cout<< "Starting vertex (root): " << vStart->name << "-> ";
    while(!q.empty())
    {
        n = q.front(); 
        q.pop(); 
        for(int i = 0; i < n->adj.size(); i++)
        {
            if(n->adj[i].v->visited == false)
            {
                n->adj[i].v->visited = true; 
                n->adj[i].v->distance = n->distance + 1; 
                q.push(n->adj[i].v); 
                cout << n->adj[i].v->name <<"("<< n->adj[i].v->distance <<")"<< " ";
            }
        }
        n->visited = true; 
    }
}



int Graph::getConnectedBuildings()
{
    int counter = 0; 
    for(int i = 0; i<vertices.size(); i++)
    {
        vertices[i]->visited = false; 
    }
    for(int i = 0; i< vertices.size(); i++)
    {
        if(vertices[i]->visited ==  false)
        {
            vertices[i] -> visited = true; 
            vertex* n; 
            queue<vertex*> q; 
            q.push(vertices[i]); 
            while(!q.empty())
            {
                n = q.front(); 
                q.pop(); 
                for(int i = 0; i < n->adj.size(); i++)
                {
                    if(n->adj[i].v->visited == false)
                    {
                        n->adj[i].v->visited = true; 
                        q.push(n->adj[i].v); 
                    }
                }
                n->visited = true; 
            }
            counter++; 
        }
    }
    return counter; 
}




