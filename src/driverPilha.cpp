#include <iostream>
#include "queue.h"

using namespace std;

int main() {

	int size = 10, i = 0;
	queue<int> pilha {size};

	cout << "------- Pushing, baby! -----------" << endl << endl;	
	while (i < 10) {	
		cout << "Testing insertion..." << endl;
		cout << "Inserting " << i << endl;
		pilha.push(i);
		cout << "Sucess! Size: " << pilha.size() << endl;
		cout << endl;
		++i;
	}
	
	cout << "------- Popping, baby! -----------" << endl << endl;	
	while (!pilha.empty()) {	
		cout << "Popping..." << pilha.front() << endl;
		pilha.pop();
		cout << "Sucess! Size: " << pilha.size() << endl;
		cout << endl;
	}
	return 0;
}
