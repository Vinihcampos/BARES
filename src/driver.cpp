#include "bares.h"
#include <iostream>
#include <string>
#include <queue>
//#include <deque>

using namespace std;

int main(){

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

	/*queue<Bares::Token> m_queue;
	queue<Bares::Token> m_queue2;
	Bares b;
	b.split(x, m_queue);
	b.infixToPostfix(m_queue, m_queue2);
	while(!m_queue2.empty()){
		cout<<m_queue2.front().symbol<<endl;
		m_queue2.pop();
	}

	cout<<"--------------------------------------------------"<<endl;

	while(!b.errors.empty()){
		cout<<b.errors.front().first<<", Coluna: "<<b.errors.front().second<<endl;
		b.errors.pop();
	}*/

	return 0;
}
