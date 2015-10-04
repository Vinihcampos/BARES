#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "bares.h"

using namespace std;

//	Priority method
int Bares::priority(string op){
	if(op == "(") 
		return 4;
	else if(op == "^")
		return 3;
	else if(op == "*" || op == "/" || op == "%") 
		return 2;
	else if(op == "+" || op == "-")
		return 1;
	else if (op == ")")
		return 0;
	else 	
		return -1;
}

//	Valid symbol method
Bares::TypeSymbol Bares::classifySymbol(char _symbol){
	if( _symbol >= '0' && _symbol <= '9' ){
		return TypeSymbol::OPERAND;
	}else if( (_symbol >= 'a' && _symbol <= 'z' ) || (_symbol >= 'A' && _symbol <= 'Z' ) ){
		return TypeSymbol::INVALID_OPERAND;
	}else if(_symbol == '+' || _symbol == '-' || 
		_symbol == '*' || _symbol == '/' ||	
		_symbol == '^' || _symbol == '%' || 
		_symbol == '(' || _symbol == ')'){
		return TypeSymbol::OPERATOR;
	}
	return TypeSymbol::INVALID_OPERATOR;
}

//	Split method
//	Verifyng errors:
// 	- 3: Invalid operand
//	- 4: Invalid operator
void Bares::tokenize(string & expression, queue<Bares::Token> & queueToken){
	Bares::Token * token = nullptr;
	int i  = 0;
	while (i < expression.size()) {
		// ignore
		if (expression[i] == ' ') { 
			++i;
			continue;
		}		
		// if its a number, check if it's negative
		bool isNegative = false;
		if (expression[i] == '-') {
			// if it's not an operand or a ')'
			if (token == nullptr || (!(token->type == TypeSymbol::OPERAND || token->symbol == ")"))) {
				isNegative = true;
				while (expression[i + 1] == '-' || expression[i] == ' ') i++;
			}
		}
		
		// check the type
		TypeSymbol type = classifySymbol(expression[i]);
		
		// new token
		token = new Bares::Token {i, type};
	
		// if it's a negative number
		if (isNegative) {
			token->type = TypeSymbol::OPERAND;
			token->symbol += "-";
			++i;
		}
		
		if (token->type == TypeSymbol::OPERAND) {
			while (type == TypeSymbol::OPERAND && i < expression.size()) {
				token->symbol += expression[i];
				i++;
				type = classifySymbol(expression[i]);
			}
		} else token->symbol += expression[i++];
		queueToken.push(*token);
	}
		/*// if it was a number before, keep that number
		if (type == TypeSymbol::OPERAND) {	
			if (token == nullptr)
				token = new Bares::Token {i, type};
			token->symbol += expression[i];
			continue;
		} else {
			if (token != nullptr)
			       queueToken.push(*token);	
			token = new Bares::Token {i, type};
			token->symbol += expression[i];
		}
		queueToken.push(*token);
		token = nullptr;
	}
	if (token != nullptr) 	
		queueToken.push(*token);
	*/
}

void printQueue(queue<Bares::Token> q){
	while (!q.empty()) {
		cout << q.front().symbol << endl;
		q.pop();
	}
	cout << endl;
}

void printStack(stack<Bares::Token> q){
	while (!q.empty()) {
		cout << q.top().symbol << endl;
		q.pop();
	}
	cout << endl;
}
//	Infix to postfix method
//	Verifyng errors:
//	- 1: Numerical constant is invalid
//	- 6: Invalid scope closure
//	- 7: Opened scope	
void Bares::infixToPostfix(queue<Bares::Token> & splittedExpression, queue<Bares::Token> & destQueue){
	stack<Bares::Token> opStack;
	
	while (!splittedExpression.empty()) {
		
		Bares::Token curToken = splittedExpression.front();
		
		switch(curToken.type) {
			case TypeSymbol::OPERAND:
				destQueue.push(curToken);
				break;
			case TypeSymbol::OPERATOR:
				bool foundOpenScope = false;
				while (!opStack.empty() && priority((opStack.top()).symbol) >= priority(curToken.symbol)) {
					if (opStack.top().symbol != "(" && opStack.top().symbol != ")")
						destQueue.push(opStack.top());
					if (curToken.symbol != ")" && opStack.top().symbol == "(") 
						break;
					if (curToken.symbol == ")" && opStack.top().symbol == "(")
						foundOpenScope = true;
					opStack.pop();
					if (foundOpenScope) break;
				}
				
				if (curToken.symbol == ")" && !foundOpenScope)
					errors.push_back({ErrorCode::INVALID_SCOPE_CLOSE, curToken});
				
				opStack.push(curToken);
				break;
		}
		splittedExpression.pop();
	}
	while (!opStack.empty()) {
		if (opStack.top().symbol == "(") 
			errors.push_back({ErrorCode::UNCLOSED_SCOPE, opStack.top()});
		
		if (opStack.top().symbol != "(" && opStack.top().symbol != ")")
			destQueue.push(opStack.top());
		opStack.pop();	
	}
	printErrors();
}

int Bares::analizeExpression(queue<Token> & _postFix, long & _result) {
	// TODO
	return 0;
}









