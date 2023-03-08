// CS311 Yoshii FALL21 - ** should be completed!!!
//
// Note that the client knows about elem.h functions.
// It can create el_t objects.
// Note that el_t X; will create a blank element X using the regular constructor.
// Note that the second constructor of el_t can be used to
// create key+other info to add to the table. e.g. el_t X(30, "mary"...);
// NEVER delete my comments!!
//-----------------------------------------------

//============================================
// HW#: HW8 hashing client
// Name: Cody McKinney
// File type: client hw8client.cpp (tester)
//===========================================

using namespace std;
#include "htable.h"
#include <iostream>
#include <fstream>
#include <string>

// Add an explanation of what this App should be used for.
// This application is to implement the functionality of my hash table methods.
// It takes in an input file of keys that represent elements of albums, including band name and year released.
// You can sort albums into the hash table and look them up using their respective key
// Using the key you can also delete existing albums, you can add new albums with new keys
// and output a new list
int main()
{
  // cout an explanation of what this App should be used for.
  cout << "CODY's FAVORITE ALBUMS" << endl;
  cout << "Hash Table composed of some of my favorite albums and favorite musicians. You can store albums with their respective band and year the album was released and a key for lookup." << endl;
  cout << "You can use the key to find or delete listings within the hash table. Can also output edited updated list to a new .txt for future reference." << endl;
  cout << endl;

  htable HT;
  string fname; // file name - decided to get the file name here
                // in the client in case the way I get them is application dependent

  cout << "What is the input file? (.txt file) ";
  cin >> fname;

  ifstream fin(fname.c_str(), ios::in);
  HT.fillTable(fin);

  // this is the output file - newout.txt
  // ofstream fout("newout.txt", ios::out);

  // make sure some of elements  collide. (Call function add)
  cout << "\nINDEX:[ (KEY: #, ALBUM, BAND, YEAR RELEASED) ]" << endl;
  cout << "==============================================" << endl;
  HT.displayTable();

  int selection;
  do
  {
    cout << "\nMENU: ---- " << endl;
    cout << "1 Add an element" << endl;
    cout << "2 Find an element" << endl;
    cout << "3 Delete an element" << endl;
    cout << "4 Display the table" << endl;
    cout << "5 Save the table to a file" << endl;
    cout << "6 Quit" << endl;
    cin >> selection;

    int thekey;
    string thename;
    el_t theelement;
    string albumName;
    int releaseDate;
    int s;

    switch (selection)
    {

    case 1: // Add and indicate slot
    {
      cout << "What is the key to add? ";
      cin >> thekey;
      cin.ignore();
      cout << "What is the name of the band? ";
      getline(cin >> std::ws, thename);
      cout << "What is the name of their album? "; //  Here get two more pieces of info
      getline(cin >> std::ws, albumName);
      cout << "What year was it released? ";
      cin >> releaseDate;
      cin.ignore();
      theelement = el_t(thekey, thename, albumName, releaseDate); //  Create the element with all the info
      s = HT.add(theelement);
      cout << "Added the element in slot " << s << endl;
      break;
    }
    case 2: // Find and indicate element
      cout << "What is the key to find? ";
      cin >> thekey;
      theelement = HT.find(thekey); // find based on thekey
      if (theelement.getkey() != -1)
      {
        cout << "Found this:" << endl;
        cout << theelement << endl;
      }
      else
      {
        cout << "Not found!" << endl;
      }

      break;

    case 3: // Delete and indicate slot
      cout << "What is the key to find? ";
      cin >> thekey;
      s = HT.deleteIt(thekey); // find and delete it based on thekey
      if (s == -1)
        cout << "Not found!" << endl;
      else
        cout << "Found it and deleted it from slot:" << s << endl;
      break;

    case 4: // Display
      cout << "The current contents are: " << endl;
      HT.displayTable();
      break;

    case 5:           // Save in the same format as input file
      HT.saveTable(); // fout);
      cout << "Saved the updated table in newout.txt" << endl;
      break;

    default:
      cout << "closing application" << endl;
    }
  } while (selection != 6);
}
