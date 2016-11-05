//
//  Stack.h
//  PA3
//
//  Created by Madeleine Monfort on 11/8/14.
//  Copyright (c) 2014 Madeleine Monfort. All rights reserved.
//

#ifndef PA3_Stack_h
#define PA3_Stack_h
#include <stdexcept>

template<typename T>
class Stack
{
    unsigned int size; //negative size isnt possible
    T* arr;
    int top;
    
public:
    Stack() { //constructor
        size = 5;
        arr = new T[size];
        top = -1; //starts out empty
    }
    
    ~Stack() { //destructor
        delete [] arr;
    }
    
    void push(const T& element) {
        if(top == size - 1) { //array is too small-full
            
            //throw std::domain_error("stack is full");
            int newSize = size*1.5; //increase array size
            T* arr2 = new T[newSize];
            for(int i = 0; i < newSize; i++) { //copy old array into new array
                arr2[i] = arr[i];
            }
            delete [] arr;
            size = newSize;
            arr = arr2;
        }
        top++;
        arr[top] = element;
        //pre increment: arr[++top];
    }
    
    T pop() {
        if(isEmpty()) {
            throw std::domain_error("ERROR: Incorrect Input");
        }
        
        if(size > 5 && (top + 1) < (size/4)) { //if array isnt being fully used
            //fix size of array
            int newSize = size/2;
            if(newSize < 5) {
                newSize = 5;
            }
            
            T* arr2 = new T[newSize];
            for(int i = 0; i < newSize; i++) {
                arr2[i] = arr[i];
            }
            delete[] arr;
            arr = arr2;
            size = newSize;
        }
        int temp = top;
        top--;
        return arr[temp];
        //post decrement: arr[top--];
    }
    
    bool isEmpty() {
        if(top == -1) {
            return true;
        }
        else {
            return false;
        }
    }
    
};

#endif
