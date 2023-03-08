//CS311 Yoshii FALL21
//INSTRUCTION:
//Look for ** to complete this program
//The string output should match my hw1queueDemo.out
// NEVER delete my comments!!!!
//=========================================================
//HW#: HW1P2 queue application (generate all strings)
//Your name: Cody McKinney
//Complier:  g++
//File type: client program client2.cpp
//===========================================================

using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "queue.h"

//Purpose of the program: Using a queue, generate all possible strings consisting of 3 characters {A, B, C}

//Algorithm:
// insert strings "A", "B", "C" in queue
// while (queue is not full) {
// 1. remove string
// 2. concatenate removed string with first character
// 3. concatenate removed string with second character
// 4. concatenate removed string with third character
// repeat until queue is full
// catch exceptions

int main()
{
  string charSet[3] = {"A", "B", "C"}; // array to hold all 3 characters
  string result;                       // variable to hold result of concatenated string
  string temp;                         // temp variable to store characters removed

  queue q; // create queue

  // insert contents of my array of characters into queue
  for (int i = 0; i < 3; i++)
  {
    q.add(charSet[i]);
    cout << charSet[i] << endl;
  }

  while (!q.isFull()) //  while loop -- indefinitely while(true)
  {
    try
    {
      q.remove(temp);       // remove first in queue
      cout << temp << endl; // display
      // loop to add the previously removed object to all elements in my array of character
      for (int i = 0; i < 3; i++)
      {
        result = temp + charSet[i];
        q.add(result); // add the new concatenated string to queue
      }
    }
    // catch underflow() overflow() errors
    catch (queue::Overflow)
    {
      // this algorithm can't cause an underflow() but I added to be general
      cerr << "ERROR: adding too many elements to the queue (overflow)! closing program!\n";
      exit(1);
    }
    catch (queue::Underflow)
    {
      cerr << "ERROR: attempting to remove from an empty queue (underflow)! closing program!\n";
      exit(1);
    }
  } // end of loop
}
