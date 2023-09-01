#include "MyStack.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

int main() {
    const char* cmd = "./calc";
    std::vector<std::string> testCases = {
        "-",
        "2 +",
        "- Unknown",
        "7.5 2.5 *",
        "0.7 0.3 %",
        "+ Unknown",
        "+",
        "a",
        "a b c",
        "5 a +",
        "+ a",
        "5 6 a +",
        "5 a 6 +",
        "a 5 6 +",
        "a b c +",
        "5 a b +",
        "5 6 a b +",
        "5 a b 6 +",
        "a b 5 6 +",
        "~ a",
        "a ~",
        "# $",
        "% &",
        "* @"
    };

    for (const auto& testCase : testCases) {
        std::cout << "Testing: " << testCase << std::endl;
        
        FILE* pipe = popen(cmd, "w");
        if (!pipe) {
            std::cerr << "Failed to run the command." << std::endl;
            return 1;
        }
        
        fprintf(pipe, "%s\n", testCase.c_str());
        pclose(pipe);
    }

    std::cout << "Testing completed." << std::endl;
    return 0;
}
