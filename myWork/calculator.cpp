//my rough stab at creating a calculator
#include<iostream>

using namespace std;

int main() {
	cout << "Enter first number: ";
	int n1;
	cin >> n1;

	cout << "Enter operator: ";
	char o;
	cin >> o;

	cout << "Enter last number: ";
	int n2;
	cin >> n2;

	cout << n1 << o << n2 << endl;

	if(o == '+') {
		cout << "= " << n1 + n2;
	}

	else if(o == '-') {
		cout << "= " << n1 - n2;
	}

	else if(o == '*') {
		cout << "= " << n1*n2;
	}

	else if(o == '/') {
		cout << "= " << n1 / n2;
	}

	else {
		cout << "Cannot compute.";
	}


	return 0;	
}