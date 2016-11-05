#include<iostream>

using namespace std;

int main()
{
	cout << "Enter size of magic square: ";

	int size;
	cin >> size;
	cout << "Your magic square is of the size: " << size << endl;

	//create array
	int *square[size];
	*square[size/2 + 1] = 1;
	

	cout << *square << endl;

	return 0;
}