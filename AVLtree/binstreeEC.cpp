// CS311 YOSHII FALL21 :
// This is the BST implementation file template by Rika Yoshii

// Each node has an Up link to make it easy to go up the tree.  It must be set as nodes are inserted.  Some deletion
// cases require Up link to be updated.  Couts are there to test to make sure
// you set the Up links correctly!!!! (Fall 19)
//
// INSTRUCTIONS:
// Look for ** comments to complete this file for HW4
// DO not delete the ** comments, but add the code next to them
// Make sure all { } match. Doing Tab on each line helps.
// Draw pictures as you complete each **
//  NEVER delete my comments!!!!
// =========================================================
// HW#: HW4 BST
// Your name: Cody McKinney
// Complier:  g++
// File type: implementation file binstree.cpp
//================================================================

#include <iostream>
#include "binstreeEC.h"
using namespace std;

// constructor  initializes Root
BST::BST()
{
  Root = NULL; // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V) // recursive post order traversal
{
  if (V != NULL)
  {
    dtraverse(V->Left);  // destroy left sub tree of V
    dtraverse(V->Right); //  destroy right sub tree of V
    delete V;            //  delete V
  }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
  std::cout << "---------------------------------" << endl;
  std::cout << "--- Elements in the IN order: ---" << endl;
  std::cout << "Root is: " << Root->Elem << endl;
  INorderTraversal(Root); // start in-order traversal from the root
  std::cout << "---------------------------------" << endl;
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
  {
    INorderTraversal(V->Left);                                                           //  traverse left sub-tree of V recursively
    cout << V->Elem << "\tHeight: " << V->Height << "  Balance: " << V->Balance << endl; //  display V's element, height and balance and do endl;
    INorderTraversal(V->Right);                                                          //  traverse right sub-tree of V recursively
  }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
bool BST::Search(el_t K)
{
  return PREorderSearch(Root, K); // start pre-order traversal from the root
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PREorderSearch(Vertex *V, el_t K)
{
  if (V != NULL)
  {
    if (K == V->Elem)
      return true; // found the element in V
    else if (V->Elem > K)
    {
      return PREorderSearch(V->Left, K); // traverse left sub-tree of V recursively
    }
    else
    {
      return PREorderSearch(V->Right, K); // traverse right sub-tree of V recursively
    }
  }
  return false;
}

// ------ The following are for adding and deleting vertices -----

// PURPOSE: Adds a vertex to the binary search tree for a new element
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
  Vertex *N;       // N will point to the new vertex to be inserted
  N = new Vertex;  // a new vertex is created
  N->Left = NULL;  // make sure it does not
  N->Right = NULL; // point to anything
  N->Elem = E;     // put element E in it
  N->Height = 0;
  N->Balance = 0;
  N->Up = NULL; // no parent for now
  cout << "Trying to insert " << E << endl;

  if (Root == NULL) // Special case: we have a brand new empty tree
  {
    Root = N; // the new vertex is added as the root
    cout << "...adding " << E << " as the root" << endl;
  } // end of the special case

  else // the tree is not empty
  {
    Vertex *V;      // V will point to the current vertex
    Vertex *Parent; // Parent will always point to V's parent

    V = Root;      // start with the root as V
    Parent = NULL; // above V so it does not point to anything

    // go down the tree until you cannot go any further
    while (V != NULL)
    {
      if (N->Elem == V->Elem) // the element already exists
      {
        cout << "...error: the element already exists" << endl;
        return;
      }
      else if (N->Elem < V->Elem) // what I have is smaller than V
      {
        cout << "...going to the left" << endl;
        Parent = V;  //  change Parent to be V to go down
        V = V->Left; // change V to be V's Left
      }
      else // what I have is bigger than V
      {
        cout << "...going to the right" << endl;
        Parent = V;   // change Parent to be V to go down
        V = V->Right; // change V to be V's Right
      }
    } // end of while

    // reached NULL -- Must add N as the Parent's child

    if (N->Elem < Parent->Elem)
    {
      Parent->Left = N; // Parent's Left should point to the same place as N
      cout << "...adding " << E << " as the left child of " << Parent->Elem << endl;
      N->Up = Parent; // N must point UP to the Parent
      cout << N->Elem << " now points UP to " << N->Up->Elem << endl;
      //** EC call here to adjust height and BF
      climbup(N);
    }
    else
    {
      Parent->Right = N; // Parent's Right should point to the same place as N
      cout << "...adding " << E << " as the right child of " << Parent->Elem << endl;
      N->Up = Parent; // N must point UP to the Parent
      cout << N->Elem << " now points UP to " << N->Up->Elem << endl;
      //** EC call here to adjust height and BF
      climbup(N);
    }

  } // end of normal case

} // end of InsertVertex

// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove
void BST::DeleteVertex(el_t E)
{
  cout << "Trying to delete " << E << endl;

  Vertex *V;      // the current vertex
  Vertex *Parent; // Parent will always point to V's parent

  // case 1: Lonely Root  --------------------
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL))
  {
    cout << "...deleting the lonely root" << endl;
    delete Root;
    Root = NULL;
    return;
  } // only the Root was there and deleted it

  // case 2:  One Substree Root ----------------
  else if (E == Root->Elem) // if what you want to delete is the root
  {
    if (Root->Left != NULL && Root->Right == NULL) // and it has only the left subtree
    {
      cout << "... deleting the root with just one child" << endl;
      Parent = Root;
      Root = Root->Left; //** change the root to the left child and return
      delete Parent;
      Root->Up = NULL; //   making sure the old root has been deleted and the new root's UP is NULL
      return;
    }
    else if (Root->Left == NULL && Root->Right != NULL) // and it has only the right subtree
    {
      cout << "... deleting the root with just one child" << endl;
      Parent = Root;
      Root = Root->Right; // change the root to the right child and return
      delete Parent;
      Root->Up = NULL; //    making sure the old root has been deleted and the new root's UP is NULL
      return;
    }
  } // end of deleting the root with one subtree

  // ---- Otherwise deleting something else  --------------

  V = Root;      // start with the root to look for E
  Parent = NULL; // above the V so does not point to anything yet

  // going down the tree looking for E
  while (V != NULL)
  {
    if (E == V->Elem) // found it
    {
      cout << "...removing " << V->Elem << endl;
      remove(V, Parent); // call remove here to remove V
      return;
    }

    else if (E < V->Elem)
    {
      cout << "...going to the left" << endl;
      Parent = V; // update Parent and V here to go down
      V = V->Left;
    }
    else
    {
      cout << "...going to the right" << endl;
      Parent = V; // update Parent and V here to go down
      V = V->Right;
    }

  } // end of while

  // reached NULL  -- did not find it
  cout << "Did not find the key in the tree." << endl;

} // end of DeleteVertex

// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  if (V->Left == NULL && V->Right == NULL) // if V is a leaf (case 1)
  {
    cout << "removing a leaf" << endl;
    if (V == P->Left) // if V is a left child of P
    {
      delete V; // delete V and also make Parent's left NULL
      P->Left = NULL;
      // ** EC call here from P to adjust height and BF
      climbup(P);
    }
    else // V is a right child of the Parent
    {
      delete V; // delete V and also make Parent's right NULL
      P->Right = NULL;
      // ** EC call from P to adjust height and BF
      climbup(P);
    }
  } // end of leaf case

  else if (V->Left != NULL && V->Right == NULL) // if V has just the left child so bypass V (case 2)
  {
    Vertex *C = V->Left; // C is the left child
    cout << "removing a vertex with just the left child" << endl;
    if (V->Left->Elem < P->Elem) // You need if then else to determine Parent's left or right
    {
      P->Left = C; // should point to C;
      C->Up = P;   // Make C point UP to the parent;
    }
    else
    {
      P->Right = C;
      C->Up = P;
    }
    cout << C->Elem << " points up to " << C->Up->Elem << endl;
    delete V; // Be sure to delete V
              //** EC call from P to adjust height and BF
    climbup(P);
  } // end of V with left child

  else if (V->Left == NULL && V->Right != NULL) // if V has just the right child so bypass V (case 2)
  {
    Vertex *C = V->Right; // C is the right child
    cout << "removing a vertex with just the right child" << endl;
    if (V->Right->Elem > P->Elem) // You need if then else to determine Parent's left or right
    {
      P->Right = C; // should point to C;
      C->Up = P;    // Make C point UP to the parent;
    }
    else
    {
      P->Left = C;
      C->Up = P;
    }

    cout << C->Elem << " points up to " << C->Up->Elem << endl;
    delete V; // Be sure to delete V
    //** EC call from P to adjust height and BF
    climbup(P);
  } // end of V with right child

  else // V has two children (case 3)
  {
    cout << "removing an internal vertex with children" << endl;
    cout << "..find the MAX of its left sub-tree" << endl;
    el_t Melem;
    // find MAX element in the left sub-tree of V
    Melem = findMax(V);
    cout << "..replacing " << V->Elem << " with " << Melem << endl;
    V->Elem = Melem; // Replace V's element with Melem here
  }                  // end of V with two children

} // end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
el_t BST::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left; // start with the left child of V

  while (V->Right != NULL) // while the right child of V is still available
  {
    Parent = V; // update Parent and V to go to the right
    V = V->Right;
  }

  // reached NULL Right  -- V now has the MAX element
  el_t X = V->Elem;
  cout << "...Max is " << X << endl;
  remove(V, Parent); // remove the MAX vertex
  return X;          // return the MAX element

} // end of FindMax

// Climbs up from the vertex to compute Height and Balance Factor
// of all ancestors and displays them as they are computed.
// This should be called whenever a vertex (N) is inserted
// This should be called whenever a vertex is deleted (i.e. delete V)
void BST::climbup(Vertex *V)
{
  cout << "...Start climbing up to adjust heights ......" << endl;
  while (V != NULL)
  {
    // ** compute V->Height  based on the left/right children's heights
    if (V->Left == NULL && V->Right == NULL) // if left and right child are null
    {
      V->Height = 0; // vertex height is zero
    }
    else if (V->Left == NULL && V->Right != NULL) // if the left child is null but right is not
    {
      V->Height = V->Right->Height + 1; // height is 1 more than the right
    }
    else if (V->Left != NULL && V->Right == NULL) // if the left child is not null and the right is null
    {
      V->Height = V->Left->Height + 1; // height is 1 more than the left
    }
    else if (V->Left != NULL && V->Right != NULL) // if both left and right are not null
    {
      V->Height = max(V->Left->Height, V->Right->Height) + 1;
    }

    // ** compute V->Balance based on the left/right children's heights
    if (V->Left != NULL && V->Right == NULL) // if left is not null but right is null
    {
      V->Balance = (-1) - V->Left->Height; // right is null so right height is (-1)
    }
    else if (V->Left == NULL && V->Right != NULL) // if left is null but right is not null
    {
      V->Balance = V->Right->Height - (-1); // left is null so left height is (-1)
    }
    else if (V->Left != NULL && V->Right != NULL) // if both left and right are not null
    {
      V->Balance = V->Right->Height - V->Left->Height; // Balance Factor is Right Height - Left Height
    }
    else if (V->Height == 0)
    {
      V->Balance = 0;
    }

    cout << "..." << V->Elem << "'s height: " << V->Height << " with balance: " << V->Balance << endl;

    if (V->Balance == -2 || V->Balance == 2) // if the balance is -2 or 2 the tree us unbalanced
    {
      fixIt(V); // fix the subtree w root V
    }

    // ** go up to the parent
    V = V->Up;
  }
}

// PURPOSE: fixIt() determines the case for the unbalanced tree and calls the appropriate method to rotate the tree into balance
// PARAMETER: Vertex *, takes a vertex pointer that represents the root of a subtree that is unbalanced
void BST::fixIt(Vertex *Red)
{
  cout << ">>>Fixing an unbalanced node at " << Red->Elem << endl;

  Vertex *Pivot;
  if (Red->Balance == 2 && Red->Right->Balance == 1) // case 1: Single Left Rotation is required because it became right heavy
  {
    cout << "   case 1: right heavy so rotate to left" << endl;
    Pivot = rotateLeft(Red);
  }

  // handle all other cases here
  else if (Red->Balance == -2 && Red->Left->Balance == -1) // case 2 Single Right Rotation is required because it became left heavy
  {
    cout << "   case 2: left heavy so rotate to right" << endl;
    Pivot = rotateRight(Red);
  }

  else if (Red->Balance == 2 && Red->Right->Balance == -1) // case 3 Double Left Rotation is required because it became right heavy (with left heavy substree)
  {
    cout << "   case 3: right heavy so double rotate to left" << endl;
    Pivot = rotateLeftDouble(Red);
  }

  else if (Red->Balance == -2 && Red->Left->Balance == 1) // case 4 Double Right Rotation is required because it became left heavy (with right heavy substree)
  {
    cout << "   case 4: left heavy so double rotate to right" << endl;
    Pivot = rotateRightDouble(Red);
  }

  // if the Root of the tree becomes the Vertex that was unbalanced, output the new Root
  if (Root == Red)
  {
    Root = Pivot; // new Root
    cout << "   New root is: " << Root->Elem << endl;
  }
  cout << ">>>Fixed" << endl;
  Display();
}

// PURPOSE: rotateLeft() rotates an unbalanced vertex to the right
// PARAMETER: Vertex *, takes in an unbalanced vertex
// Case 1 : Single Left Rotation is required because it became right heavy
Vertex *BST::rotateLeft(Vertex *Red)
{
  cout << " -- rotate left with pivot  " << Red->Right->Elem << endl;

  Vertex *Pivot;
  Pivot = Red->Right;  // Pivot is to the right of unbalanced vertex, Red
  Pivot->Up = Red->Up; // Pivot up points to what was above Red
  if (Red->Up != NULL) // if the unbalanced vertex was a subtree
  {
    Red->Up->Right = Pivot; // the vertex that was pointing to Red now points to Pivot
  }
  Red->Right = Pivot->Left; // left child of pivot becomes right child of red

  if (Pivot->Left != NULL) // if Pivot has a left child
  {
    Pivot->Left->Up = Red; // Pivots left child now points up to Red
  }
  Pivot->Left = Red; // pivots left child becomes Red
  Red->Up = Pivot;   // update up link from Red to Pivot

  updateHeightBalance(Red);
  return Pivot;
}

// PURPOSE: rotateRight() rotates an unbalanced vertex to the right
// PARAMETER: Vertex *, takes in an unbalanced vertex
// Case 2: Single Right Rotation is required because it became left heavy
Vertex *BST::rotateRight(Vertex *Red)
{
  cout << " -- rotate right with pivot  " << Red->Left->Elem << endl;
  Vertex *Pivot;
  Pivot = Red->Left;   // Pivot is to the left of unbalanced vertex, Red
  Pivot->Up = Red->Up; // Pivot points up to what Red had above it
  if (Red->Up != NULL) // if Red was a subtree of another vertex
  {
    Red->Up->Left = Pivot; // the parent of Red now points to Pivot
  }

  Red->Left = Pivot->Right; // Red's left becomes Pivot's right
  Red->Up = Pivot;          // Red points up to Pivot
  if (Pivot->Right != NULL) // if Pivot has a right child
  {
    Pivot->Right->Up = Red; // that right child now points up to Red
  }
  Pivot->Right = Red; // Red becomes the right child of Pivot

  updateHeightBalance(Red);
  return Pivot;
}

// PURPOSE: rotateLeftDouble() rotates the right subtree of an unbalanced vertex, then rotates the subtree from the unbalanced vertex
// PARAMETER: Vertex *, takes in an unbalanced vertex
// Case 3: Double Left Rotation is required because it became right heavy (with left heavy substree)
Vertex *BST::rotateLeftDouble(Vertex *Red)
{
  Vertex *Pivot;
  Vertex *Green = Red->Right; // Green is the right child vertex to our unbalanced vertex Red
  cout << " -- rotate left with pivot  " << Green->Left->Elem << endl;
  Pivot = Green->Left;        // Pivot is to the left of Green
  Pivot->Up = Red;            // Pivot now points up to Red
  Red->Right = Pivot;         // Reds right child is now Pivot
  Green->Left = Pivot->Right; // Green's left child is Pivots right child
  if (Pivot->Right != NULL)   // if Pivot has a right child
  {
    Pivot->Right->Up = Green; // Pivots right child now points up to Green
  }
  Pivot->Right = Green; // Pivots right child is Green
  Green->Up = Pivot;    // Green points up to Pivot

  updateHeightBalance(Green); // update height and balance of tree from Green

  Pivot = Red->Right; // Pivot is Reds right child
  cout << " -- rotate right with pivot  " << Pivot->Elem << endl;
  Pivot->Up = Red->Up; // Pivot points up to Reds parent
  if (Red->Up != NULL) // if Red had a parent
  {
    Red->Up->Left = Pivot; // that parent now points to Pivot
  }

  Red->Right = Pivot->Left; // Reds right child points to what Pivots left child pointed to

  Pivot->Left = Red; // Pivot points left to Red
  Red->Up = Pivot;   // Red points up to Pivot

  updateHeightBalance(Red);
  return Pivot;
}

// PURPOSE: rotateRightDouble() rotates the left subtree of an unbalanced vertex, then rotates the subtree from the unbalanced vertex
// PARAMETER: Vertex *, takes in an unbalanced vertex
// Case 4: Double Right Rotation is required because it became left heavy (with right heavy substree)
Vertex *BST::rotateRightDouble(Vertex *Red)
{
  Vertex *Pivot;
  Vertex *Green = Red->Left; // Green is the left child of our unbalanced vertex
  cout << " -- rotate left with pivot  " << Green->Right->Elem << endl;
  Pivot = Green->Right;       // Pivot becomes Greens right child
  Pivot->Up = Red;            // Pivot points up to Red
  Red->Left = Pivot;          // Pivot becomes Reds left child
  Green->Right = Pivot->Left; // Green points right to what is the left child of Pivot
  if (Pivot->Left != NULL)    // if Pivot has a left child
  {
    Pivot->Left->Up = Green; // the left child now points up to Green
  }
  Pivot->Left = Green; // Pivot points left to Green
  Green->Up = Pivot;   // Green points up to Pivot

  updateHeightBalance(Green); // update height and balance of tree from Green

  Pivot = Red->Left; // Pivot points to Reds left child
  cout << " -- rotate right with pivot  " << Pivot->Elem << endl;
  Pivot->Up = Red->Up; // Pivot up points to Reds parent
  if (Red->Up != NULL) // if Red has a parent
  {
    Red->Up->Right = Pivot; // Then the parent points right to Pivot
  }

  Red->Left = Pivot->Right; // Reds left child points to Pivots right child

  Pivot->Right = Red; // Pivots right child points to Red
  Red->Up = Pivot;    // Red points up to Pivot

  updateHeightBalance(Red);
  return Pivot;
}

// PURPOSE: updateHeightBalance() updates the Height and Balance from a Vertex that was rotated
// PARAMETER: Vertex *, takes a vertex that has just been rotated to update Height / Balance
void BST::updateHeightBalance(Vertex *Red)
{
  while (Red != NULL)
  {
    // determine Height of vertex
    if (Red->Left == NULL && Red->Right == NULL)
    {
      Red->Height = 0;
    }
    else if (Red->Left == NULL && Red->Right != NULL)
    {
      Red->Height = Red->Right->Height + 1;
    }
    else if (Red->Left != NULL && Red->Right == NULL)
    {
      Red->Height = Red->Left->Height + 1;
    }
    else if (Red->Left != NULL && Red->Right != NULL)
    {
      Red->Height = max(Red->Left->Height, Red->Right->Height) + 1;
    }

    // determine Balance of vertex
    if (Red->Left == NULL && Red->Right == NULL)
    {
      Red->Balance = 0;
    }
    else if (Red->Left != NULL && Red->Right == NULL)
    {
      Red->Balance = (-1) - Red->Left->Height;
    }
    else if (Red->Left == NULL && Red->Right != NULL)
    {
      Red->Balance = Red->Right->Height - (-1);
    }
    else if (Red->Left != NULL && Red->Right != NULL)
    {
      Red->Balance = Red->Right->Height - Red->Left->Height;
    }
    Red = Red->Up; // shift vertex up until hitting NULL
  }
}