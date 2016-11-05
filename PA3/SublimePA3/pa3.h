//
//  Pa3.h
//  PA3
//
//  Created by Madeleine Monfort on 11/6/14.
//  Copyright (c) 2014 Madeleine Monfort. All rights reserved.
//

#ifndef PA3_Pa3_h
#define PA3_Pa3_h
#include "Stack.h"
#include "Queue.h"
#include <string>
using namespace std;

class Parser {
public:
    Parser(string input); //constructor
    Queue<string>* parse();
        
private:
    void parseSpaces();
    void parseLowerCase();
    bool isNum(char c);
    bool isLetter(char c);
    bool isOperator(char c);
    bool isFunction(string str);
    bool isP(char c);
    void tokenize(string input);
    Queue<string>* outputQ;
    string input;
};

class RpnParser {
public:
    RpnParser(Queue<string>* input); //constructor
    Queue<string>* shuntparse();
    //following functions are public so Calculator class can use them
    bool isFunction(string str);
    bool isNum(string str);
    bool isOp(string str);
    
private:
    Stack<string> opStack;
    Queue<string>* inputQ;
    Queue<string>* outputQ;
};

class Calculator {
public:
    Calculator(Queue<string>* inputQ); //constructor
    double calculate();
    
private:
    double doOpMath(string op, double a, double b);
    double doFuncMath(string func, double a);
    Queue<string>* inputQ;
    RpnParser* n;
    Stack<double> numStack;
};



#endif