// CS311 Yoshii FALL21 dgraph.cpp
//  INSTRUCTION:
//    Complete all the functions you listed in dgraph.h
//    Comment the file completely using How to Comment file.
//    Use HW6-help.docx to finish the functions.
//   NEVER delete my comments!!!
//-------------------------------------------------------

//======================================================
// HW#: HW6 dgraph
// Name: Cody McKinney
// File Type: dgraph.cpp implementation file
//========================================================

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "dgraph.h"

// PURPOSE: Constructor for dgraph
dgraph::dgraph()
{
  for (int i = 0; i < SIZE; i++)
  {
    // initialize vertexName (blank) and visit numbers (0) for all slots of the table
    Gtable[i].vertexName = ' ';
    Gtable[i].visit = 0;
  }
  countUsed = 0; // initialize countUsed to be 0
}

// PURPOSE: Destructor for dgraph
dgraph::~dgraph() // do we have to delete all nodes of slists in table??
// Question: If we do not do this, will the llist destructor be called automatically??? Try it.
// The llist destructor is called automatically
{
}

// PURPOSE: fill the dgraph table with information from a text file
// reads in a vertex name, an out degree, and adds adjacent vertices to an slist
void dgraph::fillTable() // be sure to read from a specified file
{
  string fname;
  cout << "Enter a file name: ";
  cin >> fname;
  ifstream fin(fname.c_str(), ios::in); // declare and open fname

  // the rest is in HW6-help
  char X;
  int edges;
  // while we can read in a vertexName
  while (fin >> Gtable[countUsed].vertexName)
  {
    // read in the out degree
    fin >> Gtable[countUsed].outDegree;
    edges += Gtable[countUsed].outDegree;

    // loop to add adj vertices to the rear of slist
    for (int i = 1; i <= Gtable[countUsed].outDegree; i++)
    {
      fin >> X;                                    // read in adj vertex char
      (Gtable[countUsed].adjacentOnes).addRear(X); // you will have to use a linked list function addRear.
    }
    countUsed++; // increment countUsed
  }
  fin.close(); // close file
  cout << "** The number of edges is: " << edges << endl;
}

// PURPOSE: display formatted contents of our dgraph
void dgraph::displayGraph() // be sure to display
// you will have to use a linked list function displayAll.
{ // in a really nice table format -- all columns but no unused rows and include the total number of edges at the top
  cout << "   Out   Visit   Adjacency" << endl;
  cout << "-------------------------------" << endl;

  // loop to print out formatted dgraph
  for (int i = 0; i < countUsed; i++)
  {
    cout << Gtable[i].vertexName << "   ";
    cout << Gtable[i].outDegree << "\t   " << Gtable[i].visit << "\t ";
    (Gtable[i].adjacentOnes).displayAll();
  }
}

// PURPOSE: finds the number of out edges for a given vertex V
// PARAMETER: char V - the vertex we are trying to find the out degree for
// RETURNS: int - the outDegree value
int dgraph::findOutDegree(char V) // throws exception if not found
{                                 // does not use a loop - go directly to a slot using V
  int vertex = (int)V - 65;       // change character to int A = 0

  if (Gtable[vertex].vertexName == V)
  {
    return Gtable[vertex].outDegree;
  }
  else
  {
    throw BadVertex();
  }
}

// PURPOSE: to find all adjacent vertices to a given vertex V
// PARAMETER: char V - the vertex we are trying to find adjacent vertices to
// RETURNS: slist - searchable link list that holds the adjacent vertices
slist dgraph::findAdjacency(char V) // throws exception if not found
{                                   // does not use a loop - go directly to a slot using V
  int vertex = (int)V - 65;         // change character to int A = 0

  if (Gtable[vertex].vertexName == V)
  {
    return Gtable[vertex].adjacentOnes;
  }
  else
  {
    throw BadVertex();
  }
}
