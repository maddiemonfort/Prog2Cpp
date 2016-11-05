/************************************************
Testing code for the more-advanced generic LL

Expected output:
	1 10 11 12 
	[1, 10, 11, 12]
	[12, 11, 10, 1]
	<empty list>
	z c d e 
	[z, c, d, e]
	[e, d, c, z]
	<empty list>
	[e, d, c, z]
	the list contains 'd'
	the list does not contain 'm'

************************************************/

#include "LLg.h"
#include<iostream>
using namespace std;

bool same_char(const char& a, const char& b )
// this is passed to the contains function in class LL
{
	return a == b;
}

int main()
{
	LL<int> l;
	l.insert(0, 8);
	l.insert(1, 9);
	l.insert(2, 11);
	l.insert(3, 13);
	l.insert(4, 12);
	// 8, 9, 11, 13, 12
	
	l.insert(2, 10);
	// 8, 9, 10, 11, 13, 12
	
	l.remove(4);
	// 8, 9, 10, 11, 12
	
	//new
	l.push_back(13);
	// 8, 9, 10, 11, 12, 13
	
	l.pop_back();
	// 8, 9, 10, 11, 12
	
	l.pop_front();
	// 9, 10, 11, 12
	
	l.replace(0, 1);
	// 1, 10, 11, 12
	
	// test the print and item_at methods
	int size = l.size();
	for (int i = 0; i < size; ++i)
	{
		cout << l.item_at(i) << " ";
	}
	// 1, 10, 11, 12
	cout << endl;
	
	l.print(cout);
	// 1, 10, 11, 12
	cout << endl;
	
	l.reverse();
	l.print(cout);
	// 12, 11, 10, 1
	cout << endl;
	
	l.clear();
	l.print(cout);
	// <empty list>
	cout << endl;
	
	//
	
	LL<char> l2;
	l2.insert(0, 'a');
	l2.insert(1, 'b');
	l2.insert(2, 'd');
	l2.insert(3, 'f');
	l2.insert(4, 'e');
	// a, b, d, f, e
	
	l2.insert(2, 'c');
	// a, b, c, d, f, e
	
	l2.remove(4);
	// a, b, c, d, e
	
	l2.push_back('f');
	// a, b, c, d, e, f
	
	l2.pop_back();
	// a, b, c, d, e
	
	l2.pop_front();
	// b, c, d, e
	
	l2.replace(0, 'z');
	// z, c, d, e
	
	// test the print and item_at methods
	size = l2.size();
	for (int i = 0; i < size; ++i)
	{
		cout << l2.item_at(i) << " ";
	}
	// z, c, d, e
	cout << endl;
	
	l2.print(cout);
	// z, c, d, e
	cout << endl;
	
	l2.reverse();
	l2.print(cout);
	// e, d, c, z
	cout << endl;
	
	LL<char> l3 = l2; // uses the overloaded = operator
	
	l2.clear();
	l2.print(cout);
	// <empty list>
	cout << endl;
	
	l3.print(cout); // l3 should not change when l2 is changed
	// e, d, c, z
	cout << endl;
	
	if(l3.contains('d', same_char)) // yes
	{
		cout << "the list contains \'d\'" << endl;
	}
	else
	{
		cout << "the list does not contain \'d\'" << endl;
	}
	
	if(l3.contains('m', same_char)) // no
	{
		cout << "the list contains \'m\'" << endl;
	}
	else
	{
		cout << "the list does not contain \'m\'" << endl;
	}
	
	return 0;
}
