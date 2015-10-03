#include "bares.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Node{
	string symbol;
	int index;
	Node(string _symbol, int _index) : symbol {_symbol}, index {_index}{};
};

int main(){
	
	string x = "(2900000ab.= +3) * 8";
	queue<Bares::Node> m_queue;
	queue<Bares::Node> m_queue2;
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
	}

	return 0;
}