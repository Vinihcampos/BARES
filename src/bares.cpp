#include <iostream>
#include <string>
#include <stack>
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include <cmath>
#include "bares.h"

using namespace std;

bool Bares::evaluate(string & expression, int & result) {
	Queue<Token> tokens(expression.length() * 3);
	tokenize(expression, tokens);

	Queue<Token> posfix(expression.length() * 3);
	infixToPostfix(tokens, posfix);
	
	analizeExpression(posfix, result);
	
	if (errors.size() > 0) {
		return false;
	}
	
	return true;
}

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

void printQueue(Queue<Bares::Token> q){
	while (!q.empty()) {
		cout << "Taken: " << q.front().symbol << endl;
		q.pop();
	}
	cout << endl;
}
//	Split method
//	Verifyng errors:
// 	- 3: Invalid operand
//	- 4: Invalid operator
void Bares::tokenize(string & expression, Queue<Bares::Token> & queueToken){
	Bares::Token * token = nullptr;
	int i  = 0;
	while (i < expression.size()) {
		// ignore
		if (expression[i] == ' ') { 
			++i;
			continue;
		}		
		
		// if it's a number, check if it's negative in potential based on the preceding symbol
		bool isNegative = false;
		int qtdMinus = 1;
		if (expression[i] == '-') {
			// if the preceding element is not an operand or a ')'
			if (token == nullptr || (!(token->type == TypeSymbol::OPERAND || token->symbol == ")"))) {
				isNegative = true; // it can be negative, but we need to check the symbol after
				while (expression[i + 1] == '-' || expression[i + 1] == ' ') {
				 	if (expression[i + 1] == '-') ++qtdMinus;
					i++;
				} // throws out the ' ' and '-' in excess
			}
		}
		
		// check the type
		TypeSymbol type = classifySymbol(expression[i]);
		
		// new token
		if(token != nullptr)
			delete token;
		token = new Bares::Token {i, type};
	
		// if it's a negative number in potential
		if (isNegative) {
			//check the element after, to see if it's an operand
			if ((i + 1) < expression.size()) { 
				if(classifySymbol(expression[i + 1]) == TypeSymbol::OPERAND) {
					// we say it's a operand in fact!
					token->type = TypeSymbol::OPERAND;
					type = TypeSymbol::OPERAND;
					if (qtdMinus % 2 != 0) {
						token->symbol += "-";
						// and go to the number
					}
					++i;
				} else if (expression[i + 1] == '(') {
					if (qtdMinus % 2 != 0) {
						Bares::Token * t; 
						t = new Bares::Token {0, TypeSymbol::OPERAND, "-1"};
						queueToken.push(*t);
						delete t;
						t = new Bares::Token {0, TypeSymbol::OPERATOR, "*"};
						queueToken.push(*t);
						delete t;
					}
					++i;
					continue;
				}
			}
		}
		
		if (type == TypeSymbol::OPERAND) {
			// if its an operand, get all the numbers after it and assemble the whole number
			while (type == TypeSymbol::OPERAND && i < expression.size()) {
				token->symbol += expression[i];
				i++;
				type = classifySymbol(expression[i]);
			}
			// if there wasn't any number after the - sign, it is a binary operator, not a unary!
			if (token->symbol == "-") {
				token->type = TypeSymbol::OPERATOR;
			}
		} else token->symbol += expression[i++];
		// conclude operation, enqueue the new token
		queueToken.push(*token);
	}
	delete token;
}



void printStack(Stack<Bares::Token> q){
	while (!q.empty()) {
		cout << "Token: "<< q.top().symbol << endl;
		q.pop();
	}
	cout << endl;
}


//	Infix to postfix method
//	Verifyng errors:
//	- 1: Numerical constant is invalid
//	- 6: Invalid scope closure
//	- 7: Opened scope	
void Bares::infixToPostfix(Queue<Bares::Token> & splittedExpression, Queue<Bares::Token> & destQueue){
	Stack<Bares::Token> opStack;
	
	while (!splittedExpression.empty()) {
		
		Bares::Token curToken = splittedExpression.front();
		
		switch(curToken.type) {
			case TypeSymbol::OPERAND:
				destQueue.push(curToken);
				break;
			case TypeSymbol::OPERATOR: {
				bool foundOpenScope = false;
				while (!opStack.empty() && priority((opStack.top()).symbol) >= priority(curToken.symbol)) {
					// avoid operators != of ')' to take off "(" elements
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
				
				if (curToken.symbol != ")") 
					opStack.push(curToken);
				break;
			}
			case TypeSymbol::INVALID_OPERAND:
				errors.push_back({ErrorCode::INVALID_OPERAND, curToken});
				break;
			case TypeSymbol::INVALID_OPERATOR:
				errors.push_back({ErrorCode::INVALID_OPERATOR, curToken});
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
}

int Bares::analizeExpression(Queue<Bares::Token> & _postFix, int & _result) {
	Stack <Bares::Token> stackOp;
	Token op1;
	Token op2;
	while(!_postFix.empty()){
		if(_postFix.front().type == TypeSymbol::OPERATOR){
			if(!stackOp.empty()){
				op2 = stackOp.top();
				stackOp.pop();

				if(!stackOp.empty()){
					op1 = stackOp.top();
					stackOp.pop();

					if(realizeOperation(op1, op2, _postFix.front().symbol)){
						stackOp.push(op1);
					}
					else{
						errors.push_back({ErrorCode::DIVISION_BY_ZERO, _postFix.front()});
					}
				}else{
					errors.push_back({ErrorCode::LACKING_OPERAND, _postFix.front()});
				}
			}else{
				errors.push_back({ErrorCode::LACKING_OPERAND, _postFix.front()});
			}
		}else{
			stackOp.push(_postFix.front());
		}
		_postFix.pop();
	}
	Token result;
	int first = 0;
	while(!stackOp.empty()){
		if(!first){
			result = stackOp.top();
			++first;
		}else{
			result = stackOp.top();
			errors.push_back({ErrorCode::LACKING_OPERATOR, stackOp.top()});
			++first; 
		}
		stackOp.pop();
	}

	if(first == 1){
		return _result = stoi(result.symbol, nullptr, 10);
	}
	else
		return 0; 
}

bool Bares::realizeOperation(Bares::Token & op1, Bares::Token & op2, string _symbol){
	int _op1 = stoi(op1.symbol, nullptr, 10);
	int _op2 = stoi(op2.symbol, nullptr, 10);
	
	int result;
	
	switch(_symbol[0]){
		case '^':
			result = pow(_op1, _op2);
			break;
		case '*':
			result = _op1 * _op2;
			break;
		case '/': 
			if(_op2 != 0)
				result = _op1 / _op2;
			else 
				result = 0;
			break;
		case '%':
			if(_op2 != 0)
				result = _op1 % _op2;
			else
				result = 0;
			break;
		case '-':
			result = _op1 - _op2;
			break;
		default:
			result = _op1 + _op2;
			break;
	}

	op1.symbol = to_string(result);
	if( result == 0 && ( _symbol == "/" || _symbol == "%" ) && _op2 == 0)
		return false;

	return true;
}

