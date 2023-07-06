#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string caprot(int num, string passcode) {
  /*
  The user inputs an integer number and a string passcode. The passcode can have numbers and letters and symbols. The importance is   the letters that are capitlized. When the program finds a letter that is capitlized a counter begins and find the next letter to  
  capitlized. shifting the capitlization by the number the user inputed. The program needs the passcode from left to right first      and then right to left completing a loop and also shifting the cap the other way.
  */
  long int i;
  string edited_pass = passcode; //copies the string. the copied string will have the new changes
  int string_size = passcode.size() * 2; // The int Im going to use for the while loop to look after character twice left to right     and then right to left
  long int forward_counter = 0; //we add to this counter
  long int backwards_counter = -1; // we subtract from this counter
  
  for (i = 0; i < string_size; ++i) {
    if ((forward_counter+1) == (string_size/2)) { // checks if we reached the end of the passcode going forward
      passcode = edited_pass;
      if (isalpha(passcode[backwards_counter])) {
        if (isupper(passcode[backwards_counter])) {
          edited_pass[backwards_counter-num] = toupper(edited_pass[backwards_counter-num]);
          edited_pass[backwards_counter] = tolower(edited_pass[backwards_counter]);
          }
        }
      backwards_counter -= 1;
      }
  
      
    else {
      if (isalpha(passcode[forward_counter])) {
        if (isupper(passcode[forward_counter])) {
          edited_pass[forward_counter+num] = toupper(edited_pass[forward_counter+num]);
          edited_pass[forward_counter] = tolower(edited_pass[forward_counter]);
          }
        }
      forward_counter += 1;
      }

  }

  return edited_pass;
}


int main() {
  int num;
  string pass;

  cin >> num;
  getline(cin, pass);
  string new_pass = caprot(num, pass);
  cout << new_pass;
  
  return 0;
}