//
//  main.cpp
//  PA2
//
//  Created by Madeleine Monfort on 10/14/14.
//  Copyright (c) 2014 Madeleine Monfort. All rights reserved.
//

#include <iostream>
#include <ostream>
#include "pa2.h"
#include <string>
#include <locale>

int main(int argc, const char * argv[]) {
    
    bool best = true;
    if(argv[1] == NULL) {
        cout << "Error, please specify 'best' or 'worst'." << endl;
        return 0;
    }

    else {
        string bestStr = argv[1];
        if(bestStr.compare("best") == 0) {
            best = true;
        }
        else if(bestStr.compare("worst") == 0) {
            best = false;
        }
        else {
            cout << "Error, please specify 'best' or 'worst'." << endl;
            return 0;
        }
    }

    LL<string> l;
    l.createMem("None");
    
    int n = 0;
    while(true) {
        cout << "1. Add Program\n2: Kill Program\n3: Fragmentation\n4: Print Memory\n5: Exit\n" << endl;
        cin >> n;
        cout << endl;
        
        switch (n) {
            case 1: {
                cout << "Program Name: ";
                string name;
                cin >> name;
                
                if(l.iterateNum(name) != 32) {
                    cout << "\n\nError, program is already running.\n\n";
                    break;
                }
                if(name == "None") {
                    cout << "\n\nError, you cannot add this program.\n\n";
                    break;
                }
                
                cout << "Program Size (KB): ";
                int s;
                cin >> s;
                if(s/4 > 32) {
                    cout << "\n\nError, there is not enough memory for program.\n\n";
                    break;
                }
                
                if (s%4 == 0) {
                    s = s/4;
                }
                else {
                    s = s/4 + 1;
                }
                
                l.allocate(best, name, &s);
                cout << endl;
                break;
            }
            case 2: {
                cout << "Program Name: ";
                string name;
                cin >> name;
                
                l.killProgram(name);
                cout << endl;
                break;
            }
            case 3: {
                int f = l.fragmentCounter();
                cout << "There are " << f << " fragment(s)."<< endl;
                break;
            }
            case 4: {
                l.printMem();
                break;
            }
            default: {
                return 0;
            }
        }
    }
    
    return 0;
}