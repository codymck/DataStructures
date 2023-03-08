// CS311 Yoshii FALL21 Complete all functions with their comments
// NEVER delete my comments!!
// ====================================================
// HW#: HW3P1 slist  inheriting from llist
// Your name: Cody McKinney
// Complier:  g++
// File type: slist.cpp implementation file
//=====================================================

using namespace std;
#include <iostream>
#include "slist.h"

// ** Make sure llist constructor and destructors have couts in them

// PURPOSE: constructor for slist
// PARAMETER: NA
//  do not change this one
slist::slist()
{
  // cout << "slist constructor: " << endl;
}

// PURPOSE: search for a specific element in the slist
// PARAMETER: el_t key: is the element we are searching for
int slist::search(el_t key)
{
  // set P pointing to front of list
  Node *P = Front;
  // position starting at 1
  int position = 1;

  // while P does not point to NULL
  while (P != NULL)
  {
    // if P points to a node whose element is the key
    if (P->Elem == key)
    {
      return position; // return position of that node
    }
    else
    {
      position++; // else we increment our position
    }
    P = P->Next; // and shift P to the next node
  }
  // if key was not found, exit while loop and return 0
  return 0;
}

el_t slist::search2(el_t X)
{
  el_t M; // blank
  //  X has only the ID part set.
  //  In the slist look for matching el_t in Elem (the same code as search)
  //  Return the el_t obj or if not found
  //  return a blank object M

  // set P pointing to front of list
  Node *P = Front;

  // while P does not point to NULL
  while (P != NULL)
  {
    // if P points to a node whose element is the key
    if (P->Elem == X)
    {
      return P->Elem; // return position of that node
    }
    P = P->Next; // and shift P to the next node
  }

  // if key was not found, exit while loop and return blank element
  return M;
}

// PURPOSE: replace an element of the node indexed by position
// PARAMETER: el_t element: the element we are replacing with
//            int pos: the position of the element we are replacing
void slist::replace(el_t element, int pos)
{
  // don't forget to throw OutOfRange for bad pos
  // You must use moveTo to go to the pos
  if (pos > Count || pos < 1) // if position index is larger than list or less than 1
  {
    throw OutOfRange(); // throw out of range error
  }
  else
  {
    Node *R;           // node being replaced
    moveTo(pos, R);    // move R to the position if the index is valid
    R->Elem = element; // R node element is our new element
  }
}

// PURPOSE: determine if 2 slists equal each other
// PARAMETER: const slist &OtherOne: another slist we are checking if they are equal
bool slist::operator==(const slist &OtherOne)
{
  Node *P = Front;
  Node *Q = OtherOne.Front;

  // if not the same length, return false immediately
  if (this->Count != OtherOne.Count)
  {
    return false;
  }
  else if (P == NULL && Q == NULL) // if P and Q both start with NULL they are the same
  {
    return true;
  }
  else
  {
    while (P != NULL && Q != NULL) // while P and Q are not NULL
    {
      if (P->Elem == Q->Elem) // if their values are the same, P and Q will shift to next node
      {
        P = P->Next;
        Q = Q->Next;
      }
      else // if the two elements are not the same, the list is not the same
      {
        return false;
      }
    }
  }

  // if both lists have met all of these requirements they are the same, return true
  return true;
}
