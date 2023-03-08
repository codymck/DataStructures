// CS311 Yoshii
// INSTRUCTION:
// Llist class - header file template
// You must complete the ** parts and then complete llist.cpp
// Don't forget PURPOSE and PARAMETERS

// =======================================================
// HW#: HW3P1 llist
// Your name: Cody McKinney
// Compiler:  g++
// File type: headher file  llist.h
//=======================================================

// alias el_t : element type definition
typedef char el_t; // char for now but can change later

// a list node is defined here as a struct Node for now
struct Node
{
  el_t Elem;  // elem is the element stored
  Node *Next; // next is the pointer to the next node
};
//---------------------------------------------------------

class llist
{

protected:
  Node *Front; // pointer to the front node
  Node *Rear;  // pointer to the rear node
  int Count;   // counter for the number of nodes

  // untility function to move to a specified node position
  void moveTo(int, Node *&);

public:
  // Exception handling classes
  class Underflow
  {
  };
  class OutOfRange
  {
  }; // thrown when the specified Node is out of range

  llist();  // constructor to create a list object
  ~llist(); // destructor to destroy all nodes

  // PURPOSE: checks to see if list is empty
  // PARAMETER: none
  bool isEmpty();

  // PURPOSE: displays elements of all nodes in list
  // PARAMETER: none
  void displayAll();

  // PURPOSE: add a new node to the front of the list
  // PARAMETER: el_t: the element of our new node
  void addFront(el_t);

  // PURPOSE: add a node to the rear of list
  // PARAMETER: el_t: the element of the new node
  void addRear(el_t);

  // PURPOSE: delete the node at the front of the list
  // PARAMETER: el_t &: is the element of the node being removed at the front of the list
  void deleteFront(el_t &);

  //---------------------------------------

  // PURPOSE: delete a node at the rear
  // PARAMETER: el_t &: the element being returned from the Rear node being deleted
  void deleteRear(el_t &);

  // PURPOSE: delete a specific node given thru the int I key, and return the deleted element to OldNum thru pass by reference
  // PARAMETER: int: the index of the node we are searching to delete
  //            el_t &: is the element of the node being deleted
  void deleteIth(int, el_t &); // calls moveTo

  // PURPOSE: insert a node at the Ith position of the list
  // PARAMETER: int: integer key representing the index position of our new inserted value
  //            el_t: element of our newly inserted node
  void insertIth(int, el_t); // calls moveTo

  // PURPOSE: Copy Constructor to allow pass by value and return by value of a llist
  // PARAMETER: const llist &: llinked list address of the list we are copying
  llist(const llist &);

  // PURPOSE: Overloading of = (returns a reference to a llist)
  // PARAMETER: const llist &: llinked list address of the list we are getting from
  llist &operator=(const llist &);
};
