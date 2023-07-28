// This is calc.cpp
#include "Stack.h"

#include <iostream>
#include <sstream>
#include <cmath>

bool is_operator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "~";
}

double apply_operator(double a, double b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if(b == 0.0){
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    }
    if (op == "%") {
        if(b == 0.0){
            throw std::runtime_error("Division by zero");
        }
        return std::fmod(a, b);
    }
    if (op == "^") return std::pow(a, b);
    throw std::runtime_error("Unknown token");
}

int main() {
    Stack* mathstack = Stack::create();
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string token;
        bool error = false;

        while (iss >> token) {
            if (is_operator(token)) {
                if (mathstack->is_empty()) {
                    std::cout << "Not enough operands." << std::endl;
                    error = true;
                    break;
                }

                double b = mathstack->pop();

                if (token == "~") {
                    mathstack->push(-b);
                } else {
                    if (mathstack->is_empty()) {
                        std::cout << "Not enough operands." << std::endl;
                        error = true;
                        break;
                    }

                    double a = mathstack->pop();
                    try {
                        double result = apply_operator(a, b, token);
                        mathstack->push(result);
                    } catch (std::runtime_error& e) {
                        std::cout << e.what() << std::endl;
                        error = true;
                        break;
                    }
                }
            } else {
                try {
                    double value = std::stod(token);
                    mathstack->push(value);
                } catch (std::invalid_argument&) {
                    std::cout << "Unknown token." << std::endl;
                    error = true;
                    break;
                }
            }
        }

        if (error || mathstack->is_empty()) {
            if (mathstack->is_empty()) {
                std::cout << "No expression." << std::endl;
            } else {
                std::cout << "Too many operands." << std::endl;
            }
            continue;
        }

        double result = mathstack->top();
        std::cout << "= " << result << std::endl;
        mathstack->clear();
    }

    delete mathstack;  // don't forget to delete the pointer
    return 0;
}
