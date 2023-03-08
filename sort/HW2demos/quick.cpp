// CS311 Quick Sort - plug in your partition and it should work
//----------------------------------------------------------------

#include <iostream>
using namespace std;

// partitions the array a into smaller than pivot and others.
int partition(int a[], int f, int r)
{
  cout << ".. Partition called with "
       << "front " << f << " and rear " << r << endl;
  // ** your partition here but it needs to
  // ** set the pivot to a[0] at the start
  int pivot = a[f]; // pivot is the first element
  int small = f;    // pointer from the left
  int large = r;    // pointer from the right

  int temp; // placeholder for swapping

  while (small <= large) //until they cross
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
    while (a[large] > pivot) // while large is greater than our pivot
    {
      large--; // shift large to the left
    }

    // after shifting our large and small index while we can
    // if the small is still less than or equal to large
    if (small <= large)
    {
      temp = a[small];     // temp variable holds the value at our small position
      a[small] = a[large]; // variable at small index, becomes the variable at large index
      a[large] = temp;     // set large index to the original small index variable held in temp
      small++;             // increment small
      large--;             // decrement large
    }
  } //end of while

  // return the partition point where
  // those smaller than pivot are before what is returned
  // there is a special cases and a regular case

  return small; // returns the finished index of small, this represents the index of the first large value
}

// sorting a's section starting at f and ending at r
void quicksort(int a[], int f, int r)
{
  if (f >= r)
    return;

  cout << "QuickSort front is " << f << " and rear is " << r << endl;

  int beg = partition(a, f, r);

  quicksort(a, f, beg - 1); // sort the small section in place
  quicksort(a, beg, r);     // sort the large section in place
}

int main()
{
  int x;
  int nums[10];
  cout << "How many elements? (must be less than 10) ";
  cin >> x;
  cout << "Enter elements one per line.." << endl;
  for (int i = 0; i < x; i++)
  {
    cin >> nums[i];
  }

  quicksort(nums, 0, x - 1);

  cout << "FINAL RESULT:" << endl;
  for (int i = 0; i < x; i++) // up to the partition
  {
    cout << nums[i];
  }
  cout << endl;
}
