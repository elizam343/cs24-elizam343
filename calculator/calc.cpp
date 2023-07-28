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
        if (b == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }
    if (op == "%") {
        if (b == 0) {
            throw std::invalid_argument("Modulo by zero");
        }
        return std::fmod(a, b);
    }
    if (op == "^") return std::pow(a, b);
    if (op == "~") return -a; // Negates the number
    return 0.0; // Operator not supported, but this should never happen in valid input.
}


int main() {
    Stack* mathstack = Stack::create();
    std::string line;

    while (std::getline(std::cin, line)) {
        if(line.empty()) {
            std::cout << "No expression." << std::endl;
            continue;
        }

        std::istringstream iss(line);
        std::string token;
        bool error = false;

        while (iss >> token) {
            try {
                if (is_operator(token)) {
                    if (mathstack->is_empty()) {
                        std::cout << "Not enough operands." << std::endl;
                        error = true;
                        break;
                    }

                    double b = mathstack->pop();
                    double a = 0.0;

                    if (token != "~") {
                        if (mathstack->is_empty()) {
                            std::cout << "Not enough operands." << std::endl;
                            error = true;
                            break;
                        }

                        a = mathstack->pop();
                    }

                    double result = apply_operator(a, b, token);
                    mathstack->push(result);
                } else {
                    double value = std::stod(token);
                    mathstack->push(value);
                }
            } catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
                error = true;
                break;
            } catch (std::out_of_range& e) {
                std::cout << "Unknown token." << std::endl;
                error = true;
                break;
            }
        }

        if (error) {
            while (!mathstack->is_empty()) mathstack->pop();
            continue;
        }

        if (mathstack->is_empty()) {
            std::cout << "No expression." << std::endl;
            continue;
        }

        double result = mathstack->pop();
        if (!mathstack->is_empty()) {
            std::cout << "Too many operands." << std::endl;
            while (!mathstack->is_empty()) mathstack->pop();
            continue;
        }

        std::cout << "= " << result << std::endl;
    }

    delete mathstack;  // don't forget to delete the pointer
    return 0;
}

