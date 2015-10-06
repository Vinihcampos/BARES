#include "bares.h"
#include <iostream>
#include <string>
#include "queue.h"
#include <fstream>

using namespace std;

int main(int argsize, char * argsi[]){
	
	/*-------------------------------------
	 * Preparing for reading the input file.
	 * ------------------------------------*/	
	// check execution
	if (argsize == 1) {
		cerr << "Wrong sintaxe: please provide an input file." << endl;	
		return 0;
	}
	// declaring input stream
	ifstream ifs;
	// opening input file
	ifs.open(argsi[1]); 
	if (!ifs.is_open()) {
		cerr << "Unable to open input file." << endl;
		return 0;
	}
	cout << ">>> Input file (" << argsi[1] << ") opened!" << endl;
	
	/*-------------------------------------
	 * Preparing for writing an output file.
	 * ------------------------------------*/
	// output stream
	ofstream ofs; 		
	// if user wants an output file
	if (argsize == 3) {
		ofs.open(argsi[2]);
		if (!ofs.is_open()) {
			cerr << "Error on opening output file." << endl;
			return 0;
		}
	}

	string line;

	while (getline(ifs, line)) {
		Bares bares;
		int res;
		if (ofs.is_open())
			ofs << "Evaluated expression: " << line << endl;
		else
			std::cout << "Evaluated expression: " << line << endl;

		if(bares.evaluate(line, res)) {
			if (ofs.is_open())
				ofs << res << endl<<endl;
			else
				cout << res << endl<<endl;
		} else {
			if (ofs.is_open())
				bares.printErrors(ofs);
			else	
				bares.printErrors(std::cout);
		}
	}
	std::cout << "\nEnd of BARES." << endl;

	return 0;
}
