//
//  main.cpp
//  PA3
//
//  Created by Madeleine Monfort on 11/6/14.
//  Copyright (c) 2014 Madeleine Monfort. All rights reserved.
//

#include <iostream>
#include <string>
#include "Pa3.h"
#include "Stack.h"
#include "Queue.h"
#include <string>
#include <cmath>
#define PI 3.14159265

using namespace std;

int main() {
    cout << "Please insert your well-parenthesized expression." << endl;
    string input;
    getline(cin, input);
    
    try {
        Parser* parser = new Parser(input);
        Queue<string>* expression = parser->parse();
    
        RpnParser* rpnparser = new RpnParser(expression);
        Queue<string>* rpnexp = rpnparser->shuntparse();
        
        Calculator* calc = new Calculator(rpnexp);
        double answer = calc->calculate();
        
        cout << "The result is: " << answer << endl;

    }
    catch (exception& e) {
        cout << e.what() << endl;
    }
        
    return 0;
}

Parser::Parser(string input) {
    this->input = input;
    outputQ = new Queue<string>();
}

Queue<string>* Parser::parse() {
    parseSpaces();
    parseLowerCase();
    
    tokenize(input);
    
    return outputQ;
}

void Parser::parseSpaces() {
    string temp = "";
    for(int i = 0; i < input.length(); i++) {
        if(input[i] != ' ') {
            temp = temp + input[i];
        }
    }
    input = temp;
}

void Parser::parseLowerCase() {
    string temp = "";
    for(int i = 0; i < input.length(); i++) {
        if(input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] + 32;
            temp = temp + input[i];
        }
        else {
            temp = temp + input[i];
        }
    }
    input = temp;
}

bool Parser::isNum(char c) {
    if(c >= '0' && c <= '9') {
        return true;
    }
    else {
        return false;
    }
}

bool Parser::isLetter(char c) {
    return (c >= 'a' && c <= 'z') ? true : false;
}

bool Parser::isFunction(string str) {
    if(str == "sin" || str == "cos" || str == "log" || str == "sqrt") {
        return true;
    }
    else {
        return false;
    }
}

bool Parser::isOperator(char c) {
    if (c == '+' || c == '*' || c == '/' || c == '^') {
        return true;
    }
    else {
        return false;
    }
}

bool Parser::isP(char c) {
    return (c == '(' || c == ')') ? true : false;
}

void Parser::tokenize(string input) {
    bool isNumPrevious = false;
    bool isNumCurrent = false;
    bool isLetPrevious = false;
    bool isLetCurrent = false;
    string temp = "";
    
    for (int i = 0; i < input.length(); i++) {
        isNumPrevious = isNumCurrent;
        isNumCurrent = isNum(input[i]);
        isLetPrevious = isLetCurrent;
        isLetCurrent = isLetter(input[i]);
        
        if(isNumCurrent) {
            temp = temp + input[i];
            if((i + 1) == input.length()) {
                outputQ->enqueue(temp);
            }
        }
        if(isNumPrevious && !isNumCurrent) {
            outputQ->enqueue(temp);
            temp = "";
        }
        if(isLetCurrent) {
            temp = temp + input[i];
        }
        if(isLetPrevious && !isLetCurrent) {
            if(isFunction(temp)) {
                outputQ->enqueue(temp);
                temp = "";
            }
            else {
                temp = "";
                throw invalid_argument("ERROR: Unrecognized function.");
            }
        }
        if(isOperator(input[i]) || isP(input[i])) {
            temp = temp + input[i];
            outputQ->enqueue(temp);
            temp = "";
        }
        if(input[i] == '-') {
            if(input[i - 1] == '(' && isNum(input[i + 1])) {
                temp = temp + input[i];
            }
            else {
                temp = temp + input[i];
                outputQ->enqueue(temp);
                temp = "";
            }
        }
        if(!isNumCurrent && !isLetCurrent && !isOperator(input[i]) && !isP(input[i]) && input[i] != '-') {
            throw invalid_argument("ERROR: Invalid Argument.");
        }
    }
}

RpnParser::RpnParser(Queue<string>* inputQ) {
    outputQ = new Queue<string>();
    this->inputQ = inputQ;
}

Queue<string>* RpnParser::shuntparse() {
    while(!inputQ->isEmpty()) {
        string token = inputQ->dequeue();
        if(isNum(token)) {
            outputQ->enqueue(token);
        }
        else if(isOp(token)) {
            opStack.push(token);
        }
        else if(isFunction(token)) {
            opStack.push(token);
        }
        else if(token == "(") {
            opStack.push(token);
        }
        else if(token == ")") {
            string op = "";
            while(op != "(") {
                if(op != "") {
                    outputQ->enqueue(op);
                }
                op = opStack.pop();
            }
            if(!opStack.isEmpty()) {
                op = opStack.pop();
                if(isFunction(op)) {
                    outputQ->enqueue(op);
                }
                else {
                    opStack.push(op);
                }
            }
        }
    }
    if(inputQ->isEmpty()) {
        string temp = "";
        while (!opStack.isEmpty()) {
            temp = opStack.pop();
            if(temp == ")" || temp == "(") {
                throw invalid_argument("ERROR: Mismatched Parentheses");
            }
            outputQ->enqueue(temp);
        }
    }
    return outputQ;
}

bool RpnParser::isFunction(string str) {
    if(str == "sin" || str == "cos" || str == "log" || str == "sqrt") {
        return true;
    }
    else {
        return false;
    }
}

bool RpnParser::isNum(string str) {
    string temp = "";
    bool num = true;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            num = true;
        }
        else {
            num = false;
        }
    }
    if(str[0] == '-' && str.length() > 1) {
        num = true;
    }
    return num;
}

bool RpnParser::isOp(string str) {
    if(str == "+" || str == "-" || str == "*" || str == "/" || str == "^") {
        return true;
    }
    else {
        return false;
    }
}

Calculator::Calculator(Queue<string>* inputQ) {
    this->inputQ = inputQ;
    n = new RpnParser(inputQ);
}


double Calculator::calculate() {
    while (!inputQ->isEmpty()) {
        string token = inputQ->dequeue();
        if(n->isNum(token)) {
            double value = atof(token.c_str());
            numStack.push(value);
        }
        if(n->isOp(token)) {
            double a = numStack.pop();
            double b = numStack.pop();
            double value = doOpMath(token, a, b);
            numStack.push(value);
        }
        if(n->isFunction(token)) {
            double a = numStack.pop();
            double value = doFuncMath(token, a);
            numStack.push(value);
        }
    }
    double answer = numStack.pop();
    
    if(!numStack.isEmpty()) {
        throw invalid_argument("ERROR: There are too many arguments.");
    }
    
    if (answer == INFINITY) {
        throw invalid_argument("ERROR: Division by zero");
    }
    
    return answer;
}

double Calculator::doOpMath(string op, double a, double b) {
    double answer = 0.0;
    if(op == "+") {
        answer = a + b;
    }
    else if(op == "-") {
        answer = b - a;
    }
    else if(op == "*") {
        answer = a * b;
    }
    else if(op == "/") {
        answer = b / a;
    }
    else if(op == "^") {
        answer = pow(b, a);
    }
    
    return answer;
}

double Calculator::doFuncMath(string func, double a) {
    double answer = 0.0;
    if(func == "sin") {
        answer = sin(a * PI / 180);
    }
    else if(func == "cos") {
        answer = cos(a * PI / 180);
    }
    else if(func == "log") {
        answer = log2(a);
    }
    else if(func == "sqrt") {
        answer = sqrt(a);
    }
    
    return answer;
}