#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string caprot(long int num, const string& passcode) {
    string edited_pass = passcode;
    long int string_size = passcode.size();

    for (long int i = 0; i < string_size; ++i) {
        if (isupper(passcode[i])) {
            long int rotated_index = (i + num) % string_size;
            edited_pass[rotated_index] = toupper(edited_pass[rotated_index]);
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
