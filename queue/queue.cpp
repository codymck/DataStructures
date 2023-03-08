//INSTRUCTION: FALL21
//Look for ** using control-S
//Then, fill in the function body
//When done, compile queue.cpp to make sure it has no syntax errors
// NEVER delete my comments!!!
//=========================================================
//HW#: HW1P2 queue
//Your name: Cody McKinney
//Complier:  g++
//File type: queue implementation queue.cpp
//===========================================================

using namespace std;
#include <iostream>
#include "queue.h"

// constructor
queue::queue()
{ // initialize data members as in the notes
  front = 0;
  rear = -1;
  count = 0;
}

//destructor
queue::~queue()
{ // nothing
}

// PURPOSE: returns true if queue is empty, otherwise false - checks count
bool queue::isEmpty()
{
  if (count == 0)
  { // if the count is 0, the queue is empty
    return true;
  }

  return false;
}

// PURPOSE: returns true if queue is full, otherwise false - checks count
bool queue::isFull()
{
  if (count == MAX_SIZE)
  { // if the count is equal to the maximum size, the queue is full
    return true;
  }

  return false;
}

// PURPOSE: if full, throws an exception Overflow
// if not full, enters an element at the rear
// PAREMETER: provide the element (newElem) to be added
void queue::add(el_t newElem)
{
  if (isFull())
  { // if the queue is full no new elements can be added, handle with exception
    throw Overflow();
  }

  rear = (rear + 1) % MAX_SIZE; // rear is incremented, checking for max size to loop queue
  el[rear] = newElem;           // element at rear becomes the passed element
  count++;                      // increment count
}

// PURPOSE: if empty, throw Underflow
// if not empty, removes the front element to give it back
// PARAMETER: provide a holder (removedElem) for the element removed (pass by ref)
void queue::remove(el_t &removedElem)
{
  if (isEmpty())
  { // if queue is empty no elements can be removed, handle with exception
    throw Underflow();
  }

  removedElem = el[front];        // remove element at the current front index
  front = (front + 1) % MAX_SIZE; // front is incremented, checking for max size to loop queue
  count--;                        // decrement count because an element has been removed

  // if the queue is empty we reset position of front and rear
  if (count == 0)
  {
    front = 0;
    rear = -1;
  }
}

// PURPOSE: if empty, throws an exception Underflow
// if not empty, give back the front element (but does not remove it)
//PARAMETER: provide a holder (theElem) for the element (pass by ref)
void queue::frontElem(el_t &theElem)
{
  if (isEmpty())
  { // if queue is empty no element at front, handle with exception
    throw Underflow();
  }

  theElem = el[front]; // passed variable becomes element at the front
}

// PURPOSE: returns the current size to make it
// accessible to the client caller
int queue::getSize()
{
  return count; // returning the current count
}

// PURPOSE: display everything in the queue horizontally
// from front to rear enclosed in [   ]
// if empty, displays [ empty ]
void queue::displayAll()
{
  if (isEmpty())
  {
    cout << "[ empty ]" << endl;
  }
  else
  {
    int j = front;
    cout << "[ ";
    for (int i = 1; i <= count; i++)
    {
      cout << el[j] << " ";
      j = (j + 1) % MAX_SIZE;
    }
    cout << "]" << endl;
  }
}

// PURPOSE: if empty, throws an exception Underflow
//if queue has just 1 element, does nothing
//if queue has more than 1 element, moves the front one to the rear by
//calling remove followed by add.
void queue::goToBack()
{
  el_t temp; //  temp variable to hold value being moved to rear

  if (isEmpty())
  { // if queue is empty no value can be moved
    throw Underflow();
  }

  if (count > 1) // if queue only has 1 element we cannot swap its place, if queue is > 1 we remove and add
  {
    // remove and add
    remove(temp);
    add(temp);
  }
}
