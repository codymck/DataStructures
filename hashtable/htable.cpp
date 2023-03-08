// CS311 Yoshii FALL21 - Hash Table - complete all ** parts.
// Note: this class does not know the parts of element except for key
// so that it would work even if each element in the hash table changed
//  NEVER delete my comments!!
//-----------------------------------------------------

// ============================================
// HW#: HW8 Hash Table
// Name: Cody McKinney
// File Type: implementation htable.cpp
// =============================================

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "htable.h"

// htable Constructor
htable::htable()
{
}

// htable Destructor
htable::~htable()
{
}

// a simple hash function that uses % TSIZE simply
int htable::hash(int key)
{
  return key % TSIZE;
}

// adds the element to the table and returns slot#
int htable::add(el_t element)
{
  int slot = hash(element.getkey()); // hash with the key part
  table[slot].addRear(element);      // Note that this means adding the element to a slist in the slot (call addRear)
  return slot;
}

// finds element using the skey and returns the found element itself
// or a blank element  -- there is no cout in here
el_t htable::find(int skey)
{
  int slot = hash(skey);                    // hash with skey
  el_t selement;                            // this is the element to look for in slist
  selement.setkey(skey);                    // initialize selement with just the skey (call setkey)
  selement = table[slot].search2(selement); // call slist's search2 with selement which returns the found element
  return selement;                          // return the found element from here (it could be blank)
}

// finds the element given the key  and deletes it from the table.
//  Returns the slot number.
int htable::deleteIt(int skey)
{
  int slot = hash(skey);                       // hash with skey
  el_t selement;                               // this is the element to look for in slist
  selement.setkey(skey);                       //  initialize selement with just the skey
  int position = table[slot].search(selement); //  call slist's search which gives you the location I and then deleteIth
  try
  {
    table[slot].deleteIth(position, selement);
  }
  catch (llist::OutOfRange)
  {
    return -1;
  }

  return slot; //  return the slot number
}

// fills the table using the specified input file
void htable::fillTable(istream &fin)
{
  //  model this after HW6 to get data from the file the user specified
  //  which elem and slist functions do you call? List them here first.
  // variable declarations
  int slot;
  int akey;
  string aname;
  string album;
  int year;
  char delim;

  // while the text has a new key
  while (fin >> akey)
  {
    // take in the comma as a delimeter
    fin >> delim;
    getline(fin >> std::ws, album, ','); // get the album name as a string stopping at ','
    getline(fin >> std::ws, aname, ','); // get the band name as a string stopping at ','
    fin >> year;                         // read in year as int input

    el_t elem(akey, aname, album, year); // construct a new el_t variable with the info read in from file
    slot = hash(akey);                   // find the slot based on hashing the key
    add(elem);                           // add the new element to our hashtable
  }
}

// displays the entire table with slot#s too
void htable::displayTable()
{
  for (int i = 0; i < 37; i++)
  {
    cout << i << ":";
    table[i].displayAll(); // call slist's displayAll
  }
}

// saves into the specified file in the same format as the input file
void htable::saveTable() // ostream &fout)
{
  // this is the output file - newout.txt
  std::ofstream fout("newout.txt", ios::out);
  el_t elem;
  slist temp;
  // loop through the whole hashtable
  for (int i = 0; i < TSIZE; i++)
  {
    temp = table[i]; // copy the slist table for row i to temp
    if (temp.isEmpty())
    {
      // if temp is empty, do nothing and loop back
    }
    else
    {
      while (!temp.isEmpty()) // while the list for this row is not empty
      {
        temp.deleteFront(elem); // delete the front element
        fout << elem;           // output that element to file
        fout << endl;
      }
    }
  }
  fout << endl;
}
