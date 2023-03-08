// CS311 Yoshii FALL21 Linked List class

// INSTRUCTION:
// Must use the provided HW3P1_help.doc to create llist.cpp
// It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//   You can copy from a Word document to emacs (contrl-right click)
//   Highly recommended to copy HW3P1-help as PURPOSE of each function.
//
//- Make sure all if-then-else are commented describing which case it is
//- Make sure all local variables are described fully with their purposes
//   NEVER delete my comments!!!!
// EMACS HINT:
//   cntr-K cuts and cntr-Y pastes.
//   Esc x replace-str does string replacements
//   Esc > goes to the end of the file; Esc < to the beginning
//   Tab on each line will indent perfectly for C++

// ====================================================
// HW#: HW3P1 llist
// Your name: Cody McKinney
// Complier:  g++
// File type: llist.cpp implementation file
//=====================================================

using namespace std;
#include <iostream>
#include "llist.h"

// linked list constructor initializes front and rear to NULL and sets count to 0
llist::llist()
{
  cout << "... in llist constructor..." << endl;

  Front = NULL;
  Rear = NULL;
  Count = 0;
}

// linked list destructor
llist::~llist()
{
  cout << ".... in llist destructor..." << endl;

  el_t temp; // temp variable for deleting
  while (!isEmpty())
  {
    deleteFront(temp);
  }
}

// PURPOSE: checks to see if list is empty
// PARAMETER: none
bool llist::isEmpty()
{
  if (Front == NULL && Rear == NULL && Count == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
} // be sure to check all 3 data members

// PURPOSE: displays elements of all nodes and its element in list
// PARAMETER: none
void llist::displayAll()
{
  // special case: if list is empty
  if (isEmpty())
  {
    cout << "[ empty ]" << endl; // print empty list
    return;
  }

  cout << "[ ";
  Node *P;   // create a node P
  P = Front; // P is pointing to our front node

  while (P != NULL) // while P is pointing to a node that is not NULL
  {
    cout << P->Elem << " "; // print the element P is pointing to and
    P = P->Next;            // and advance P to the next node
  }

  cout << "]" << endl;
} // be sure to display horizontally in [  ] with
// blanks between elements e.g. [ 1 2 3 4]
// You MUST use while (P != NULL) loop or you will not get the credit!

// PURPOSE: add a node to the rear of list
// PARAMETER: el_t NewNum is the element of the new node
void llist::addRear(el_t NewNum)
{
  // special case: this is the very first node
  if (isEmpty())
  {
    Node *P = new Node; // create a new node
    P->Elem = NewNum;   // set the Element to NewNum

    Front = P;         // set the front to the new Node P
    Rear = P;          // set the rear to the new Node P
    Rear->Next = NULL; // set the next to NULL

    Count++; // increment count
  }
  // regular case: add a new node to the rear
  else
  {
    Rear->Next = new Node; // create a new node after the current Rear
    Rear = Rear->Next;     // update Rear to the new node
    Rear->Elem = NewNum;   // new Rear element is NewNum
    Rear->Next = NULL;     // Point Rear->Next to NULL

    Count++; // increment count
  }
} // comment the 2 cases

// PURPOSE: add a new node to the front of the list
// PARAMETER: el_t NewNum: the element of our new node
void llist::addFront(el_t NewNum)
{
  // special case: if this is the very first node
  if (isEmpty())
  {
    Node *P = new Node; // create a new node
    P->Elem = NewNum;   // element of new node is NewNum
    Front = P;          // Front points to P
    Rear = P;           // Rear points to P
    Rear->Next = NULL;  // Point Rear->Next to NULL

    Count++; // increment count
  }
  // regular case: add a new Node at the front with the element NewNum
  else
  {
    Node *newFront = new Node; // create a new node
    newFront->Elem = NewNum;   // new Node element is NewNum
    newFront->Next = Front;    // new Node points to our current Front node
    Front = newFront;          // Front updated to point to new Front node

    Count++; // increment count
  }
} // comment the 2 cases

// PURPOSE: delete the node at the front of the list
// PARAMETER: el_t OldNum: the element of the node being removed at the front of the list
void llist::deleteFront(el_t &OldNum)
{
  // error case: list is empty, throw exception
  if (isEmpty())
  {
    throw Underflow();
  }
  // special case: deleting front will make the list empty
  else if (Count == 1)
  {
    OldNum = Front->Elem; // OldNum is the element at the Front node
    delete Front;         // delete the node Front was pointing to
    Front = NULL;         // point Front to NULL
    Rear = NULL;          // point Rear to NULL

    Count--; // decrement count
  }
  // regular case: give back the Front node
  else
  {
    OldNum = Front->Elem; // OldNum is the Front nodes element
    Node *Second;         // create a new Node to represent the new front of the list
    Second = Front->Next; // point the Second node to the node after the Front node
    delete Front;         // delete Front node
    Front = Second;       // point Front node to the Second

    Count--; // decrement count
  }
} // comment the 3 cases

// PURPOSE: delete a node at the rear
// PARAMETER: el_t OldNum: the element being returned from the Rear node being deleted
void llist::deleteRear(el_t &OldNum)
{
  // error case: if empty, throw exception
  if (isEmpty())
  {
    throw Underflow();
  }
  // special case: this is going to make the list empty
  else if (Count == 1)
  {
    OldNum = Rear->Elem; // OldNum is the Rear node element
    delete Rear;         // delete the node Rear is pointing to
    Rear = NULL;         // point Rear to NULL
    Front = NULL;        // point Front to NULL

    Count--; // decrement count
  }
  // regular case: give back the rear node element and remove rear node
  else
  {
    OldNum = Rear->Elem; // OldNum is the Rear node element

    Node *newRear = Front; // make a temporary node pointing to the front of list

    // while the next node is not the rear node
    while (newRear->Next != Rear)
    {
      newRear = newRear->Next; // shift through nodes until the node before rear
    }

    delete Rear;       // delete the Rear node
    Rear = newRear;    // point Rear to newRear
    Rear->Next = NULL; // set our new Rear's next node to NULL

    Count--; // decrement count
  }
} // comment the 3 cases

/* --- harder ones for case 2 and 3 follow -- */

// Utility Function to move a local pointer to the Jth node
// PURPOSE: move a pointer to a specific node
// PARAMETER: int J: an integer key for the specific node
//            Node *&temp: a temporary node pointer
void llist::moveTo(int J, Node *&temp)
{ // moves temp J-1 times to go to the Jth node
  // for ( int K = ... ) temp = temp->Next;
  temp = Front;
  for (int K = 1; K <= J - 1; K++)
  {
    temp = temp->Next;
  }
}

// PURPOSE: delete a specific node given thru the int I key, and return the deleted element to OldNum thru pass by reference
// PARAMETER: int I: the index of the node we are searching to delete
//            el_t &OldNum : is the element of the node being deleted
void llist::deleteIth(int I, el_t &OldNum)
{
  // error case: I is an illegal value
  if (I > Count || I < 1)
  {
    throw OutOfRange();
  }
  // special case 1: being deleted from the front
  else if (I == 1)
  {
    deleteFront(OldNum);
  }
  // special case 2: being deleted from the rear
  else if (I == Count)
  {
    deleteRear(OldNum);
  }
  // regular case: delete the Ith node
  else
  {
    Node *X;                // initialize X node
    Node *Q;                // initialize Q node
    moveTo(I - 1, X);       // move X to the node right before the node being deleted
    moveTo(I + 1, Q);       // move Q to the node right after the node being deleted
    OldNum = X->Next->Elem; // OldNum is the element of the Ith node we are deleting
    delete X->Next;         // delete the Ith node
    X->Next = Q;            // the node after X is now our node that trailed our Ith node

    Count--; // decrement count
  }
} // must use moveTo to move local pointers. Be sure to comment to which node you are moving them. Do not forget to set OldNum.

// PURPOSE: insert a node at the Ith position of the list
// PARAMETER: int I: integer key representing the index position of our new inserted value
//            el_t newNum: element of our newly inserted node
void llist::insertIth(int I, el_t newNum)
{
  // error case: I is an illegal value
  if (I > (Count + 1) || I < 1)
  {
    throw OutOfRange();
  }
  // special case 1: inserting to the front of list
  else if (I == 1)
  {
    addFront(newNum);
  }
  // special case 2: inserting at the rear of list
  else if (I == (Count + 1))
  {
    addRear(newNum);
  }
  // regular case add a node right before the current Ith node
  else
  {
    Node *P;            // node P will point to the node before I
    Node *X = new Node; // node X is our new node being inserted at I
    Node *Q;            // Q is our current Ith node that will come after our new node X
    moveTo(I - 1, P);   // P is right before our Ith node
    moveTo(I, Q);       // Q points to our Ith node
    P->Next = X;        // P->Next now points to our X node
    X->Elem = newNum;   // X element now holds our newNum
    X->Next = Q;        // our original Ith node is now after our new X node

    Count++; // increment count
  }
} // must use moveTo to move local pointers. Be sure to comment to which node you are moving them.

// PURPOSE: copy constructor for pass by value and return by value
// PARAMETER: const llist &Original: is the original linked list we will be copying from
llist::llist(const llist &Original)
{
  // NOTE the original is being passed to the constructor by reference
  // to create a new object this-> as a copy of the original
  // this->'s data members need to be initialized first
  Front = NULL;
  Rear = NULL;
  Count = 0;

  // this-> object has to be built up by allocating new cells
  // and copying the values from original into each cell
  Node *P; // local pointer for Original
  P = Original.Front;
  while (P != NULL)
  {
    this->addRear(P->Elem);
    P = P->Next;
  }
} // use my code

// PURPOSE: allows 2 linked lists to = each other (operator overloading)
// PARAMETER: const llist &OtherOne: is a llist object that we are going to be getting from
llist &llist::operator=(const llist &OtherOne)
{
  el_t x;
  // first make sure this-> and OtherOne are not the same object
  // to do this, compare the pointers to the objects

  if (&OtherOne != this) // if not the same
  {
    // this-> object has to be emptied first
    while (!this->isEmpty())
    {
      this->deleteRear(x);
    }
    // this-> object has to be built up by allocating new cells with OtherOne elements
    // Node *P;
    // P = OtherOne.Front;
    // while (P != NULL) // a loop which repeats until you reach the end of OtherOne
    // {
    // this->addRear(P->Elem); // P's element is added to this->
    // P = P->Next;            // go to the next node in OtherOne
    //}
    *this = llist(OtherOne);
  }             // end of if
  return *this; // return the result unconditionally
  // note that the result is returned by reference
} // use my code
