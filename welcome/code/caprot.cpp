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
        if (num < 0) { // Check if we reached the end of the passcode going forward
            if (isupper(edited_pass[edited_pass.size() + backwards_counter])) {
                if ((string_size + backwards_counter + num) < 0) {
                    long int tempVal = -(string_size + backwards_counter + num);
                    edited_pass[tempVal] = toupper(edited_pass[tempVal]);
                    edited_pass[tempVal] = tolower(edited_pass[edited_pass.size() - backwards_counter - num]);
                }
                else {
                    edited_pass[edited_pass.size() + backwards_counter + num - 1] = toupper(edited_pass[edited_pass.size() - backwards_counter - num - 1]);
                    edited_pass[edited_pass.size() + backwards_counter + num] = tolower(edited_pass[edited_pass.size() - backwards_counter - num]);
                }  
                
            }
            backwards_counter -= 1;
        }
        else {
            if (isupper(passcode[forward_counter])) {
                if ((forward_counter + num) > string_size) {
                    long int tempVal = (forward_counter + num) - string_size - 1;
                    edited_pass[tempVal] = toupper(edited_pass[tempVal]);
                    edited_pass[forward_counter] = tolower(edited_pass[forward_counter]);
                }
                else {
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
        long int size = pass.size();
        if ((num > size) || (-num > size)) {
            cout << pass << endl;
        }
        else {
            string new_pass = caprot(num, pass);
            cout << new_pass << endl;
        }
    }

    return 0;
}