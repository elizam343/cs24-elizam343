#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string caprot(int num, const string& passcode) {
    string edited_pass = passcode;
    int string_size = passcode.size();

    for (int i = 0; i < string_size; ++i) {
        if (isupper(edited_pass[i])) {
            int rotated_index = (i + num) % string_size;
            edited_pass[rotated_index] = toupper(edited_pass[rotated_index]);
        }
    }

    return edited_pass;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        int num = stoi(argv[1]);
        string pass;
        getline(cin, pass);
        int size = pass.size();
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
