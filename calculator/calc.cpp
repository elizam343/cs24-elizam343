#include "Stack.h"
#include <iostream>
#include <sstream>
#include <cmath>

bool is_operator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "~";
}

double apply_operator(Stack* mathstack, const std::string& op) {
    if (mathstack->is_empty()) {
        throw std::runtime_error("Not enough operands.");
    }
    
    double b = mathstack->pop();
    
    if (op == "~") {
        return -b;
    }

    if (mathstack->is_empty()) {
        throw std::runtime_error("Not enough operands.");
    }

    double a = mathstack->pop();

    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if(b == 0.0){
            throw std::runtime_error("Division by zero.");
        }
        return a / b;
    }
    if (op == "%") {
        if(b == 0.0){
            throw std::runtime_error("Division by zero.");
        }
        return std::fmod(a, b);
    }
    if (op == "^") return std::pow(a, b);
    throw std::runtime_error("Unknown operator.");
}

int main() {
    Stack* mathstack = Stack::create();
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string token;
        bool error = false;

        // First pass: check for unknown tokens
        std::istringstream checkIss(line);  // Create a new istringstream to not disrupt the main one
        while (checkIss >> token) {
            if (!is_operator(token)) {
                try {
                    std::stod(token);  // Check if it can be converted to double
                } catch (std::invalid_argument&) {
                    std::cout << "Unknown token." << std::endl;
                    error = true;
                    break;
                }
            }
        }

        if (error) {
            continue;
        }

        // Now that we've checked for unknown tokens, let's evaluate the expression.
        while (iss >> token) {
            if (is_operator(token)) {
                try {
                    double result = apply_operator(mathstack, token);
                    mathstack->push(result);
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                    error = true;
                    break;
                }
            } else {
                try {
                    double value = std::stod(token);
                    mathstack->push(value);
                } catch (std::invalid_argument&) {
                    // We've already checked for unknown tokens, so this part shouldn't be reached.
                    // But it's good practice to keep it for robustness.
                    std::cout << "Unknown token." << std::endl;
                    error = true;
                    break;
                }
            }
        }

        if (error) {
            mathstack->clear();
            continue;
        }

        if (mathstack->is_empty()) {
            std::cout << "No expression." << std::endl;
            continue;
        }

        double result = mathstack->pop();
        if(mathstack->is_empty()) {
            std::cout << "= " << result << std::endl;
        } else {
            std::cout << "Too many operands." << std::endl;
            mathstack->clear();
        }
    }

    delete mathstack; 
    return 0;
}
