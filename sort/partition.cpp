#include <iostream>
using namespace std;

// CS311 YOSHII FALL21
// You may not change my code in any manner.  0 pts if you do!!!!!!
// Simply add your code for **
//  NEVER delete my comments!!
//----------------------------------------
// CS311 HW2P2 Partition
// Name: Cody McKinney
// Compiler: g++
//-----------------------------------------

// partitions the array a into smaller than pivot and others.
// f is the beginning of the section to be partitioned
// r is the end of the section to be partitioned
// return the first slot of the Large section
int partition(int a[], int f, int r)
{
  int pivot = a[f]; // pivot is the first element
  int small = f;    // pointer from the left
  int large = r;    // pointer from the right

  int temp; // placeholder for swapping

  while (small <= large) // until they cross
  {
    // loop for finding out of place pairs and swap them
    //    until the small and large cross
    //    if small OK, move left
    //    if large OK, move right
    //    if both are bad, swap and then move
    while (a[small] < pivot) // while small is less than our pivot
    {
      small++; // shift small to the right
    }
    while (a[large] >= pivot) // while large is greater than our pivot
    {
      large--; // shift large to the left
    }

    // after shifting our large and small index while we can
    // if the small is still less than or equal to large
    if (small <= large)
    {
      // temp = a[small];     // temp variable holds the value at our small position
      // a[small] = a[large]; // variable at small index, becomes the variable at large index
      // a[large] = temp;     // set large index to the original small index variable held in temp
      cout << "Swapping " << a[small] << " and " << a[large] << endl;
      swap(a[small], a[large]); // swaps elements at small and large index
      small++;                  // increment small
      large--;                  // decrement large
    }
  } // end of while

  // return the partition point where
  // those smaller than pivot are before what is returned
  // there is a special cases and a regular case

  if (small == 0)
  {
    return small + 1;
  }
  else
  {
    return small;
  }
  // return small; // returns the finished index of small, this represents the index of the first large value
}

int main()
{
  int x; // number of elements
  int nums[10];
  cout << "How many elements? (must be less than 10) ";
  cin >> x;
  cout << "Enter elements one per line.." << endl;
  for (int i = 0; i < x; i++)
  {
    cin >> nums[i];
  }

  // the pivot is always the first element
  cout << "Ok the pivot is " << nums[0] << endl;

  // part represents the index of our first large value
  int part = partition(nums, 0, x - 1);

  cout << "Results..." << endl;
  // display up to the partition without endl
  for (int i = 0; i < part; i++)
    cout << nums[i];

  // print barrier before our large values
  cout << "|";
  // display from the partition on.. without endl
  for (int i = part; i < x; i++)
    cout << nums[i];

  cout << endl;
}
