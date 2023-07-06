#include <iostream>
#include <string>
#include <cctype>
using namespace std;




string caprot(long int num, const string& passcode) {

    /*
    The user inputs an integer number and a string passcode. The passcode can have numbers and letters and symbols. The importance is   the letters that are capitlized. When the program finds a letter that is capitlized a counter begins and find the next letter to  
    capitlized. shifting the capitlization by the number the user inputed. The program needs the passcode from left to right first      and then right to left completing a loop and also shifting the cap the other way.
    */

    string edited_pass = passcode; //copies the string. the copied string will have the new changes
    long int string_size = passcode.size() -1; // The int Im going to use for the while loop to look after character twice left to right     and then right to left
    long int forward_counter = 0; //we add to this counter
    long int backwards_counter = -1; // we subtract from this counter
    
    
    
    for (long int i = 0; i < string_size; ++i) {
        if (forward_counter == string_size) { // Check if we reached the end of the passcode going forward
            if (isalpha(edited_pass[edited_pass.size() + backwards_counter])) {
                if (isupper(edited_pass[edited_pass.size() + backwards_counter])) {
                    edited_pass[edited_pass.size() + backwards_counter - num - 1] = toupper(edited_pass[edited_pass.size() - backwards_counter - num - 1]);
                    edited_pass[edited_pass.size() + backwards_counter - num] = tolower(edited_pass[edited_pass.size() - backwards_counter - num]);
                }
            }
            backwards_counter -= 1;
        }
        else {
            if (isalpha(passcode[forward_counter])) {
                if (isupper(passcode[forward_counter])) {
                    edited_pass[forward_counter + num] = toupper(edited_pass[forward_counter + num]);
                    edited_pass[forward_counter] = tolower(edited_pass[forward_counter]);
                }
            }
            forward_counter += 1;
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