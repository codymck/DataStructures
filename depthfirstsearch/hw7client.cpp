// CS311 YOSHII FALL21

//==========================================
// HW#: HW7 DFS client using dgraph.h
// Name: Cody McKinney
// File type: client hw7client.cpp
//==========================================

// ** Be sure to include both dgraph  and stack
#include <iostream>
#include <vector>
#include "dgraph.h"
#include "stack.h"

bool hasDuplicates(vector<char>);
bool inPath(vector<char> p, char v);
ostream &operator<<(ostream &os, const vector<char> &v);

// This client uses the dgraph class and stack class
// to do depth first traversal of the graph stored in table.txt
int main()
{
  // ** copy here the algorithm (read carefully) in the HW7
  // assignment sheet and use that for the comments.
  char v; // vertex
  int visitCount = 1;
  dgraph G;      // directed graph
  stack vStack;  // vertex stack
  slist adjList; // adjacents list
  vector<char> path;

  G.fillTable();
  G.displayGraph(); // Display the graph before DFS begins.

  vStack.push('A');         // Push A onto the stack to start.
  while (!vStack.isEmpty()) // While the stack is not empty do:
  {
    vStack.pop(v);                                           // Remove a vertex v from the stack.
    cout << "Removed '" << v << "' from the stack." << endl; // Display the vertex name.  E.G. “Removed B from stack”
    if (!G.isMarked(v))                                      // If v is not marked yet (visit number is 0) then
    {
      G.visit(visitCount, v);                                  // mark it (visit it **)
      cout << "Visit '" << v << "' as " << visitCount << endl; // inform the user E.G. “Visit B as 2”
      visitCount++;

      adjList = G.findAdjacency(v); // get its adjacency list (slist)

      if (adjList.isEmpty()) // if no adjacent ones
      {
        cout << "Deadend reached - backup." << endl; // inform the user E.G. “Deadend reached – backup.”
      }
      else
      {
        // else put adjacent ones on the stack (delete from the rear and push) informing the user
        cout << "...pushing: ";
        adjList.displayAll();
        while (!adjList.isEmpty())
        {
          adjList.deleteRear(v);
          vStack.push(v);
        }
      }
    }
    else
    {
      // else inform the user E.G. “B had been visited already - backup.”
      cout << "'" << v << "' had been visited already - backup." << endl;
    }
    // Display the stack clearly labeling it as the current stack
    cout << "CURRENT ";
    vStack.displayAll();
  }
  // Display the Graph nicely with visit numbers for all vertices.

  G.displayGraph();
}

bool hasDuplicates(vector<char> p)
{
  for (int i = 0; i < p.size(); i++)
  {
    for (int j = i + 1; j < p.size(); j++)
    {
      if (p[i] == p[j])
      {
        return true;
      }
    }
  }
  return false;
}

bool inPath(vector<char> p, char v)
{
  for (int i = 0; i < p.size(); i++)
  {
    if (v == p[i])
    {
      return true;
    }
  }
  return false;
}

ostream &operator<<(ostream &os, const vector<char> &v)
{
  os << "Current Path: ";
  for (int i = 0; i < v.size(); i++)
  {
    os << v[i];
  }
  os << endl;

  return os;
}