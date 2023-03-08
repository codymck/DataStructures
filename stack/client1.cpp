//CS311 Yoshii FALL21
//INSTRUCTION:
//Look for ** to complete this program (Use control-S)
//The output should match my hw1stackDemo.out
// NEVER delete my comments !!!
//=========================================================
//HW#: HW1P1 stack application (post-fix evaluation)
//Your name: Codu McKinney
//Complier:  g++
//File type: client program client1.cpp
//===========================================================

using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "stack.h"

// Purpose of the program: This program is designed to implement stacks to evaluate post-fix expressions
/* Algorithm: 
  while there are still items left {
  try {
    1. read item in as character
    2. if it is a number, push (watch for overflow)
    3. else if item is an operator, 
              pop the last 2 numbers (watch for underflow)
              apply operator to the two numbers
              push result
    4. else if item is invalid throw exception
  } end try
  catch exceptions
 } end while
 pop the top of the stack which is the result
 or if anything is left, incomplete expression exception thrown
*/
int main()
{
  stack postfixstack; // integer stack
  string expression;  // user entered expression

  cout << "type a postfix expression: ";
  cin >> expression;

  int i = 0; // character position within expression
  char item; // one char out of the expression

  int box1; // receive things from pop
  int box2; // receive things from pop

  int result; // result of operation on box1 and box2

  while (expression[i] != '\0') // til the end of the expression
  {
    try
    {
      item = expression[i]; // current char

      // ** do all the steps in the algorithm given in Notes-2A

      // check if input is a char digit between 0 - 9
      if (item >= '0' && item <= '9')
      {
        // if yes, push the value of the character digit - '0' to the stack
        postfixstack.push(item - '0');
        postfixstack.displayAll();
      }
      // if the input is not a char digit, but one of our 3 operators
      else if ((item == '+') || (item == '-') || (item == '*'))
      {
        // pop each value to its box to hold, box2 being our first number in equations
        postfixstack.pop(box1);
        postfixstack.pop(box2);
        // if input is '+' we do addition on our two most recently popped elements
        if (item == '+')
        {
          result = box2 + box1;
        }
        // if input is '-' we do subtraction on our two most recently popped elements
        else if (item == '-')
        {
          result = box2 - box1;
        }
        // if input is '*' we do multiplication on our two most recently popped elements
        else if (item == '*')
        {
          result = box2 * box1;
        }
        // push the result of the operation onto the stack
        postfixstack.push(result);
        postfixstack.displayAll();
      }
      // if the input is neither operator or operand we throw exception
      else
      {
        throw "invalid entry";
      }

    } // this closes try
    // Catch exceptions and report problems and quit the program now (exit(1)).
    // Error messages describe what is wrong with the expression.
    catch (stack::Overflow) // calls exception if too many numbers or operands are pushed onto the stack
    {
      cerr << "ERROR: expression is too long! closing program!\n";
      exit(1);
    }
    catch (stack::Underflow) // calls exception if there are not enough numbers or operands to pop
    {
      cerr << "ERROR: too few operands/numbers! closing program!\n";
      exit(1);
    }
    catch (char const *errormsg) // for invalid item case
    {
      cerr << "ERROR: invalid input! closing program!\n";
      exit(1);
    }

    // go back to the loop after incrementing i
    i++;
  } // end of while

  // After the loop successfully completes:
  // Pop the result and show it.
  postfixstack.pop(result);
  cout << "Result: " << result << "\n";

  // If anything is left on the stack, an incomplete expression
  // was found so also inform the user.
  // if the stack is not empty, display the stack and give error message.
  if (!postfixstack.isEmpty())
  {
    postfixstack.displayAll();
    cerr << "ERROR: incomplete expression! closing program!\n"; // displays if there are numbers left on the stack and no more operations to be attempted
    exit(1);
  }

} // end of the program
