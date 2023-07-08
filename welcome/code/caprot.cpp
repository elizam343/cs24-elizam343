#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string caprot(long int num, const string& passcode) {\
    /*
  The user inputs an integer number and a string passcode. The passcode can have numbers and letters and symbols. The importance is   the letters that are capitlized. When the program finds a letter that is capitlized a counter begins and find the next letter to  
  capitlized. shifting the capitlization by the number the user inputed. The program needs the passcode from left to right first      and then right to left completing a loop and also shifting the cap the other way.
  */
    string edited_pass = passcode; //copies the string. the copied string will have the new changes
    long int string_size = passcode.size();

    for (long int i = 0; i < string_size; ++i) {
        if (num > 0) { // postive indexing
            if (isupper(passcode[i])) {
                long int rotated_index = (i + num) % string_size;
                edited_pass[i] = tolower(edited_pass[i]);
                edited_pass[rotated_index] = toupper(edited_pass[rotated_index]);
            }
        }
        else { // for negative indexing
            if (isupper(passcode[i])) {
                long int rotated_index = (i - (-num % string_size) + string_size) % string_size;
                edited_pass[i] = tolower(edited_pass[i]);
                edited_pass[rotated_index] = toupper(edited_pass[rotated_index]);
            }
        }
    }

    return edited_pass;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        long int num = stoi(argv[1]);
        string pass;
        getline(cin, pass);
        string new_pass = caprot(num, pass);
        cout << new_pass << endl;
    }

    return 0;
}
