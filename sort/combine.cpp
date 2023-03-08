using namespace std;
#include <iostream>
#include <vector>

// CS311 YOSHII FALL21
// Must use the algorithm that is in the notes!
//  NEVER delete my comments!!
//--------------------------------------------
//CS311 HW2P2 Combine
//Name: Cody McKinney
//Compiler: g++
//--------------------------------------------

// combines two sorted lists A and B into R
// displays comparison every time it is done
void combine(vector<int> A, vector<int> B, vector<int> &R)
{
  // you can find out the size of A using the
  // size function. Treat A and B like arrays.
  // be careful -- R comes in as an empty vector with no slots so you have to use push_back
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

int main()
{
  vector<int> L1;
  vector<int> L2;
  vector<int> L3;
  int N; // how many elements in each of L1 and L2
  int e; // for each element

  cout << "How many elements in each list?" << endl;
  cin >> N;

  cout << "List1" << endl;
  for (int i = 1; i <= N; i++)
  {
    cout << "element :";
    cin >> e;
    L1.push_back(e);
  }

  cout << "List2" << endl;
  for (int i = 1; i <= N; i++)
  {
    cout << "element :";
    cin >> e;
    L2.push_back(e);
  }

  // call combine here to combine L1 and L2 into L3
  combine(L1, L2, L3);

  cout << "The result is: ";
  for (int i = 0; i < N * 2; i++)
  {
    cout << L3[i];
  }
  cout << endl;

} // end of main
