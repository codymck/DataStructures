// CS311 Yoshii FALL21
// HW6 Client file
// INSTRUCTION: Complete this file and comment using How to Comment file.
//---------------------------------------------

// ================================================
// HW#: HW6 dgraph client
// Name: Cody McKinney
// File type: hw6client.cpp  (tester)
// ================================================

// includes
#include <iostream>
#include "dgraph.h"

using namespace std;

// test client
// creates a dgraph, fills the dgraph table from a text file and displays
// asks user to search for specific vertex information
// try catch for unfound vertices
int main()
{
  //**
  char input;
  // 0.Declare dgraph object
  dgraph G;
  // 1.fillTable()
  G.fillTable();
  // 2.displayGraph()
  G.displayGraph();
  // while (the user does not want to stop)
  while (input != '0')
  {
    try
    {
      // a.the user will specify which vertex
      cout << "Enter a vertex name or enter '0' to exit : ";

      cin >> input;     // take char input from user
      if (input == '0') // if the input is our sentinel value '0'
      {
        cout << "exiting ..." << endl;
        break; // end the loop
      }

      // b.findOutDegree of the vertex and display the result
      int outDeg = G.findOutDegree(input); // outDeg is the outdegree from our table G for the given char input
      cout << input << " has " << outDeg << " edges that come out to: " << endl;

      // b.findAdjacency of the vertex and display the result (see Hint)
      (G.findAdjacency(input)).displayAll(); // G.findAdjacency(input) returns an slist, and we display the slist
    }
    // c.catch exception to display error mesg but do not exit
    catch (dgraph::BadVertex)
    {
      cerr << "ERROR: no such vertex exists" << endl;
    }
  }
  // end of while
}

/*
Hint:
  slist l1;
  l1 = G.findAdjacency('a');
  // how do you display l1?  Hint: it is an slist from HW3.

*/
