#include "bares.h"
#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include 

using namespace std;

int main(int nargs, char * argsi[]){
	
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
	
	Bares bares;

	//giving the result
	if (ofs.open) {
		// TODO
	} else {
		// TODO
	}
	

	std::queue<Bares::Token> queueToken;
	std::queue<Bares::Token> queueTokenized;
	//string x = "(2900000ab.= +3) * 8";
	//string x = "***(3        + 5))))";
	//string x = "((6+3)*2 - (3-2))^(5+2)";
	//string x = "2^1*1-4+5/3/(2+2)";
	//string x = "(2+3)*(3-2)";
	//string x = "2 + 3 - 3";
	//string x = "2 + 3";
	//string x = "(-----2 * ------4)";
	//string x = "(-(";
	string x = "2-3/(3 * 2 ^ 3)";
	Bares bares;	
	
	bares.tokenize(x, queueToken);
	bares.infixToPostfix(queueToken, queueTokenized);	
	while (!queueTokenized.empty()) {
		cout << "Token: "  << (queueTokenized.front()).symbol << endl;
		queueTokenized.pop();
	}

	return 0;
}
