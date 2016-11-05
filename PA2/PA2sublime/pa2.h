//
//  LL.h
//  PA2
//
//  Created by Madeleine Monfort on 10/14/14.
//  Copyright (c) 2014 Madeleine Monfort. All rights reserved.
//

#ifndef PA2_LL_h
#define PA2_LL_h

#include<stdexcept>
#include<ostream>
#include<string>

using namespace std;

template <typename T>
class LL
{
    struct Node
    {
        T program;
        Node* next;
        bool free;
        
        Node(T program, Node* next) // constructor
        {
            this->program = program;
            this->next = next;
            free = true;
        }
        
    };
    
    Node* head;
    
public:
    LL() // constructor
    {
        head = NULL;
    }
    
    //iterator given a position
    Node* iterate(int position) {
        Node* current = head;
        for(int i = 0; i < position; i ++) {
            current = current->next;
        }
        return current;
    }
    
    //iterator that finds location of program
    int iterateNum(T program) {
        int position = 0;
        Node* current = head;
        while (current != NULL && current->program != program) {
            current = current->next;
            position++;
        }
        
        return position;
    }
    
    void insert(int position, T program)
    {
        Node* current = head;
        Node* previous = NULL;
        
        if(this->size() == 0) {
            Node* current = head;
            head = new Node(program, current);
        }
        else {
            for(int i = 0; i < position; i++) {
                previous = current;
                current = current->next;
            }
            Node* n = new Node(program, NULL);
            previous->next = n;
            n->next = current;
        }
    }
    
    //creates the initial free spaces
    void createMem(T program) {
        for(int i = 0; i < 32; i++) {
            insert(i, program);
        }
    }
    
    void printMem() {
        int temp = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 8; j++) {
                if(freeAt(temp)) {  //if there is no program (it's "free")
                    cout << "Free\t";
                }else {
                    cout << item_at(temp) << "\t"; //print out the program
                }
                temp++;
            }
            cout << endl;
        }
        cout << endl;
    }

    
    T remove(int position)
    {
        Node* current = head;
        Node* previous = NULL;
        for(int i = 0; i < position; i++) {
            previous = current;
            current = current->next;
        }
        
        previous->next = current->next;
        T data = current->program;
        delete current;
        return data;
    }

    int size()
    {
        int size = 1;
        if (head == NULL) {
            return 0;
        }
        else {
            Node* current = head;
            while (current != NULL) {
                current = current->next;
                size++;
            }
            return size;
        }
        
    }
    
    T item_at(int position)
    {
        
        if (size() == 0) {
            return head->program;
        }
        else {
            Node* current = iterate(position);
            return current->program;
        }
    }
    
    bool freeAt(int position) {
        Node* current = head;
        for(int i = 0; i < position; i++) {
            current = current->next;
        }
        return current->free;
    }
    
    void addProgram(T program, int position) {
            Node* current = iterate(position);
            current->program = program;
            current->free = false;
    }
    
    void killProgram(T program) {
        Node* current = head;
        for (int i = 0; i < size() - 1; i++) {
            if (current->program == program) {
                current->free = true;
            }
            current = current->next;
        }
    }
    
    /*allocates where to start programs and how many programs to start in the linked
     list- depending on whether to use best- or worst-fit scenario. */
    void allocate(bool best, T program, int* pages) {
        int pMax = 0;
        int pMin = 0;
        int min = 32;
        int max = 0;

        getFragmentPosition(&pMin, &pMax, &min, &max, pages);
        
        if(best == true) {
            //choose smallest fragment it fits in to put the program in
            addProgram(program, pMin);
            for (int i = 1; i < *pages; i++) {
                pMin++;
                addProgram(program, pMin);
            }
        }
        else {
            //choose the largest fragment to put the program in
            if(*pages > max) {
                cout << "\n\nError, there is not enough memory for this program.\n\n";
                return;
            }
            addProgram(program, pMax);
            for (int i = 1; i < *pages; i++) {
                pMax++;
                addProgram(program, pMax);
            }
        }
    }
    
    //get starting position of fragment and also get size of fragments
    void getFragmentPosition(int* minPos, int* maxPos, int* min, int* max, int* pages) {
        int freeNode = 0;
        int position = 0;
        *min = 32;
        *max = 0;
        
        Node* current = head;
        while (current != NULL) {
            if(current->free == true) {
                freeNode++;
                
                //conditions for the end of a fragment
                if(current->next != NULL && current->next->free == false) {
                    
                    //finding position for max fragment (worst fit)
                    if(*max < freeNode) {
                        *max = freeNode;
                        *maxPos = (position + 1) - freeNode;
                    }
                    //finding position for min fragment (best fit)
                    if(*min >= freeNode && freeNode >= *pages) {
                        *minPos = (position + 1) - freeNode;
                        *min = freeNode;
                    }
                }
                
                /*taking into account that if the next node is NULL, it is also free
                 and therefore earlier if-loop would never consider it, even though
                 it would be the end of any fragment.*/
                if(current->next == NULL) {
                    if(*max < freeNode) {
                        *max = freeNode;
                        *maxPos = (position + 1) - freeNode;
                    }
                    if(*min >= freeNode && freeNode >= *pages) {
                        *min = freeNode;
                        *minPos = (position + 1) - freeNode;
                    }
                }
            }
            else {
                freeNode = 0;
            }
            current = current->next;
            position++;
        }
    }
    
    int fragmentCounter() {
        int fragments = 0;
        Node* current = head;
        while (current != NULL) {
            if(current->free == true) {
                if(current->next != NULL && current->next->free == false) {
                    fragments++;
                }
            }
            if(current->free == true && current->next == NULL) {
                fragments++;
            }
            current = current->next;
        }
        
        return fragments;
    }

};




#endif
