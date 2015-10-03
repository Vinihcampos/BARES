#include "bares.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//	Priority method
int Bares::priority(string _symbol){
	if(_symbol == "(" || _symbol == ")")
		return 1;
	else if(_symbol == "^")
		return 3;
	else if(_symbol == "*" || _symbol == "/" || _symbol == "%") 
		return 4;
	else if(_symbol == "+" || _symbol == "-")
		return 5;
	else if((_symbol[0] >= 'a' && _symbol[0]  <= 'z' ) || (_symbol[0]  >= 'A' && _symbol[0]  <= 'Z' ) )
		return 6;
	else 
		return 7;
}

//	Valid symbol method
int Bares::validSymbol(char _symbol){
	if( _symbol >= '0' && _symbol <= '9' ){
		return 3; 
	}else if( (_symbol >= 'a' && _symbol <= 'z' ) || (_symbol >= 'A' && _symbol <= 'Z' ) ){
		return 2;
	}else if(_symbol == '+' || _symbol == '-' || 
		_symbol == '*' || _symbol == '/' ||	
		_symbol == '^' || _symbol == '%' || 
		_symbol == '(' || _symbol == ')'){
		return 1;
	}else{ 
		return 0;
	}
}

//	Split method
//	Verifyng errors:
// 	- 3: Invalid operand
//	- 4: Invalid operator
void Bares::split(string & _expression, queue<Bares::Node> & queue){
	int index = -1;
	string aux = "";
	for(auto i (0); i < _expression.length(); ++i){
		if(validSymbol(_expression[i]) == 2){
			errors.push({"Invalid operand", i + 1});
		}else if(validSymbol(_expression[i]) == 0 && _expression[i] != ' '){
			errors.push({"Invalid operator", i + 1});
		}

		if(_expression[i] != ' '){
			if(validSymbol(_expression[i]) == 3){
				if(index == -1)
					index = i + 1;
				aux += _expression[i];
			}else{
				if(aux != ""){
					queue.push({aux, index});
					index = -1;
				}
				aux = _expression[i];
				queue.push({aux, i + 1});				
				aux = "";
			}
		}
	}
	if(aux != ""){
		queue.push({aux, index});
	}
}

//	Infix to postfix method
//	Verifyng errors:
//	- 1: Numerical constant is invalid
//	- 6: Invalid scope closure
//	- 7: Opened scope	
void Bares::infixToPostfix(queue<Bares::Node> & _splittedExpression, queue<Bares::Node> & newQueue){
	stack<Bares::Node> stack;
	while(!_splittedExpression.empty()){
		if(_splittedExpression.front().symbol.length() > 1){
			int x = stoi(_splittedExpression.front().symbol, nullptr, 10);
			if( x < -32767 || x > 32767 ){
				errors.push({"Numerical constant is invalid", _splittedExpression.front().index});
			}
			newQueue.push(_splittedExpression.front());
			_splittedExpression.pop();
		}else if( priority(_splittedExpression.front().symbol) == 6 ){
			newQueue.push(_splittedExpression.front());
			_splittedExpression.pop();
		}else{
			if(stack.empty() || _splittedExpression.front().symbol == "("){
				stack.push(_splittedExpression.front());
				_splittedExpression.pop();				
			}else if(_splittedExpression.front().symbol == ")"){
				while(stack.top().symbol != "("){
					newQueue.push(stack.top());
					stack.pop();
					if(stack.empty()) {
						errors.push({"Invalid scope closure", _splittedExpression.front().index});
						break; // ERRO (VERIFICAD0 DEPOIS)
					}else if(stack.top().symbol == "(") {
						stack.pop();
						break;
					}
				}
				_splittedExpression.pop();
			}else{
				if(!stack.empty()){
					while(priority(stack.top().symbol) <= priority(_splittedExpression.front().symbol)){
						if(stack.top().symbol == "("){
							break;
						}else{
							newQueue.push(stack.top());
							stack.pop();
						}						
						if(stack.empty()) break;
					}
				}				
				stack.push(_splittedExpression.front());
				_splittedExpression.pop();
			}
		}
	}
	while(!stack.empty()){
		if(stack.top().symbol == "("){
			errors.push({"Opened scope", stack.top().index});
		}else{			
			newQueue.push(stack.top());
		}
		stack.pop();
	}
}