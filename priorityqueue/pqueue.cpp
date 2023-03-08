// CS311 Yoshii FALL21 - HW5 Priority Queue Implementation File
// Complete all ** parts and give good comments
// ** NEVER delete my comments.

// =================================================
// HW5 Priority Printer Queue
// YOUR NAME: Cody McKinney
// File Type: implementation pqueue.cpp
// =================================================

#include "pqueue.h"

// constructor
pqueue::pqueue()
{
  count = 0; // no jobs yet
}

// destructor does nothing
pqueue::~pqueue() {}

// Purpose: to add a job to a right place in the Pqueue
// Argument: j is the job priority number
// Remember that the current last job is in slot count-1.
void pqueue::insertjob(int j)
{
  cout << "Adding: " << j << endl;
  //  add the job j at the rear (and update count)
  //    if impossible else display error message.
  if (count != MAX)
  {
    Q[count] = j;
    count++;
  }
  else
  {
    cout << "ERROR: Queue is full" << endl;
  }
  trickleup(); // moves the job to the right place
}

// Purpose: to print a job and reheapify the Pqueue
void pqueue::printjob()
{
  cout << "Printing: " << Q[0] << endl;
  reheapify();
}

// Purpose: to display all jobs
void pqueue::displayAll()
{
  cout << "Jobs: ";
  // loop to display jobs from slot 0 to slot count-1 horizontally. No need to show a tree format.
  for (int i = 0; i <= (count - 1); i++)
  {
    cout << Q[i] << " ";
  }
  cout << endl;
}

// Utility functions follow: ------------------

void pqueue::swap(int loc1, int loc2)
{
  //  simply swap the values in these locations in Q
  int temp = Q[loc1];
  Q[loc1] = Q[loc2];
  Q[loc2] = temp;
}

// Purpose: to make the very last job trickle up to the right location.
// Never do X--.
void pqueue::trickleup()
{
  int x = count - 1; // the very last job's location
  int P;             // Parent index;
  //  While x is > 0
  //    compare Q[x] with the parent value (*)
  //    and if the parent value is bigger call swap & update x
  //    to be the parent location. Otherwise stop the loop.
  // (*) Call getParent to get the location of the parent
  //            based on the child's location.
  while (x > 0)
  {
    P = getParent(x);
    if (Q[x] < Q[P])
    {
      swap(x, P); // swap values when value at x index is less than value at Parent index
      x = P;      // update x to be parent location
    }
    else
    {
      return;
    }
  }
}

// Purpose: find the location of the parent
// The child location is given.  Need to call even.
int pqueue::getParent(int childloc)
{
  int P;              // parent position
  if (even(childloc)) // if child location is even
  {
    P = (childloc - 2) / 2; // then the child location is on the right
  }
  else // child location is not even
  {
    P = (childloc - 1) / 2; // then the child location is on the left
  }
  //  return the parent location based on the child loc
  return P;
}

// Purpose: is location i even? Important in finding its parent location
bool pqueue::even(int i)
{
  if ((i % 2) == 0)
    return true;
  else
    return false;
}

// Purpose: to reheapify the Pqueue after printing
//  This trickles down.  Never do X++.
void pqueue::reheapify()
{
  int X;               // the current location
  Q[0] = Q[count - 1]; // move the last job to the front
  count--;
  X = 0; //  Start X at 0 (the root)

  while (X < count - 1) // While X is within the array (the used portion):
  {
    int smaller = getSmallerchild(X); // Find the location of the smaller child by calling getSmallerchild.

    if (smaller == -1) // (if the location of both children are off the tree, stop the loop).
    {
      return;
    }
    else if (Q[X] > Q[smaller]) // If the smaller child is smaller than the parent value,
    {
      swap(X, smaller); // call swap
      X = smaller;      // and X becomes the smaller child's location
    }
    else // else no swaps so stop to loop.
    {
      return;
    }
  }
}

// Purpose: to find the location of the smaller child
// where children are at locations 2*i+1 and 2*i+2
int pqueue::getSmallerchild(int i)
{
  int LC, RC;  // locations of children
  int smaller; // location of smaller child
  // set LC and RC first.
  LC = (2 * i) + 1;
  RC = (2 * i) + 2;
  //    return the location of the smaller child
  //    Be careful because one or both of them may be
  //    beyond count-1 or just the RC is beyond count-1.
  //    Check boundaries before you
  //    compare Q contents!!!!
  //    If both are beyond count-1, you want to return a special value.
  if (LC <= (count - 1) && RC <= (count - 1))
  {
    if (Q[LC] < Q[RC]) // if left child is less than right child
    {
      smaller = LC; // left child is smaller
    }
    else // else right child is less than left child
    {
      smaller = RC; // right child is smaller
    }
  }
  else if (LC <= (count - 1) && RC > (count - 1)) // left child is in bounds but right child is not
  {
    smaller = LC; // smaller has to be left child
  }
  else // both left and right child are out of bounds
  {
    return -1; // return special value
  }

  return smaller;
}
// NEVER GO TO UNUSED PART OF THE ARRAY
