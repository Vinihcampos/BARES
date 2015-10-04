#include "bares.h"
#include <iostream>
#include <string>
#include <queue>
//#include <deque>

using namespace std;

int main(){

	std::queue<Bares::Token> queueToken;
	//string x = "(2900000ab.= +3) * 8";
	string x = "***(3        + 5))))";
	Bares bares;	
	
	bares.tokenize(x, queueToken);
	
	while (!queueToken.empty()) {
		cout << "Token: "  << (queueToken.front()).symbol << endl;
		queueToken.pop();
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
