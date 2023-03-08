// CS311 Merge Sort - plug in your combine and it should work
//--------------------------------------------------------

using namespace std;
#include <iostream>
#include <vector>

void display(vector<int> X)
{
  cout << "[ ";
  for (int i = 0; i < X.size(); i++)
    cout << X[i] << " ";
  cout << "]" << endl;
}

void Combine(vector<int> A, vector<int> B, vector<int> &R)
{
  int ia = 0; // index for A
  int ib = 0; // index for B
  int ir = 0; // index for R

  // while our indexes are still smaller than both vector sizes
  while (ia < A.size() && ib < B.size())
  {
    // if A at our index is less than B at index, push value of A at index ia to back of R
    if (A[ia] < B[ib])
    {
      R.push_back(A[ia]); // get the A element to R
      ia++;               // increment index for A
    }
    else // else B at index is less than A at index, push value of B at index ib to back of R
    {
      R.push_back(B[ib]); // get the B element to R
      ib++;               // increment index for B
    }
    cout << "comparison" << endl; // printed record of each comparison
  }

  if (ia < A.size()) // if there are still elements left in A, copy them to R
  {

    while (ia < A.size()) // while ia is less than the size of A
    {
      R.push_back(A[ia]); // push the remaining values of A onto R
      ia++;               // increment A index
    }
  }
  else // else there are elements still left in B, copy them into R
  {
    while (ib < B.size()) // while ib is less than the size of B
    {
      R.push_back(B[ib]); // push the remaining values of B onto R
      ib++;               // increment B index
    }
  }
}

// sort N into R
void MergeSort(vector<int> N, vector<int> &R)
{
  vector<int> L1, L2, L1R, L2R;

  // only one element, so done
  if (N.size() == 1)
  {
    R.push_back(N[0]);
    return;
  }

  cout << "Merge sort called on: ";
  display(N);

  // divide N into L1 and L2
  for (int i = 0; i < N.size() / 2; i++)
    L1.push_back(N[i]);
  for (int i = N.size() / 2; i < N.size(); i++)
    L2.push_back(N[i]);

  cout << "1st half:" << endl;
  display(L1);
  cout << "2nd half:" << endl;
  display(L2);

  // sort the first half and produce L1R
  MergeSort(L1, L1R);
  // sort the second half and produce L2R
  MergeSort(L2, L2R);

  // combine the sorted halves into sorted R
  Combine(L1R, L2R, R);
}

int main()
{
  vector<int> Mine, Mine2;
  int a;
  cout << "Enter elements or -1 to stop" << endl;
  cout << "Element:";
  cin >> a;
  while (a != -1)
  {
    Mine.push_back(a);
    cout << "Element:";
    cin >> a;
  }
  MergeSort(Mine, Mine2); // produce Mine2

  cout << "FINAL RESULT:" << endl;
  display(Mine2);
}
