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
				// count number of "-" signs
				while (expression[i + 1] == '-' || expression[i + 1] == ' ') {
				 	if (expression[i + 1] == '-') ++qtdMinus;
					i++;
				} 
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
			if ((i + 1) < expression.size()) { 
				//check the element after, to see if it's an operand
				if(classifySymbol(expression[i + 1]) == TypeSymbol::OPERAND) {
					// we say it's a operand in fact!
					token->type = TypeSymbol::OPERAND;
					type = TypeSymbol::OPERAND;
					// if it's negative in fact
					if (qtdMinus % 2 != 0) {
						token->symbol += "-";
					}
					// go to the number
					++i;
				// when the situation is (-(, for example
				} else if (expression[i + 1] == '(') {
					// if negative in fact
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
	// assure no memory leak
	if (token != nullptr)
		delete token;
}

void Bares::infixToPostfix(Queue<Bares::Token> & splittedExpression, Queue<Bares::Token> & destQueue){
	// stack for operators
	Stack<Bares::Token> opStack;
	int test;
	while (!splittedExpression.empty()) {
		// get token
		Bares::Token curToken = splittedExpression.front();
		// check token's type
		switch(curToken.type) {
			// operands are just sent to the queue
			case TypeSymbol::OPERAND:
				// checking if number is out of bounds
				test = stoi(curToken.symbol, nullptr, 10);
				if (test < -32786 || test > 32767)
					errors.push_back({ErrorCode::INVALID_NUMBER, curToken});
				// even if out of bounds, enqueue
				destQueue.push(curToken);
				break;
			// operators are more tricky
			case TypeSymbol::OPERATOR: {
				// to check an open scope
				bool foundOpenScope = false;
				// while top of stack has a operand with greater priority
				while (!opStack.empty() && priority((opStack.top()).symbol) >= priority(curToken.symbol)) {
					// avoid operators != of ')' to take off "(" elements
					if (opStack.top().symbol != "(" && opStack.top().symbol != ")")
						destQueue.push(opStack.top());
					// stop if found "("
					if (curToken.symbol != ")" && opStack.top().symbol == "(") 
						break;
					// stop if close scope
					if (curToken.symbol == ")" && opStack.top().symbol == "(")
						foundOpenScope = true;
					// remove operator from stack
					opStack.pop();
					// stop if close scope
					if (foundOpenScope) break;
				}
				// error - invalid scope close	
				if (curToken.symbol == ")" && !foundOpenScope)
					errors.push_back({ErrorCode::INVALID_SCOPE_CLOSE, curToken});
				// push current operator into the stack, if it's not a ")"
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
		// go to next token
		splittedExpression.pop();
	}
	// pop all remanescent operators in stack
	while (!opStack.empty()) {
		// if found a "(" that's not gonna be closed, error
		if (opStack.top().symbol == "(") 
			errors.push_back({ErrorCode::UNCLOSED_SCOPE, opStack.top()});
		if (opStack.top().symbol != "(" && opStack.top().symbol != ")")
			destQueue.push(opStack.top());
		// go to the next
		opStack.pop();	
	}
}

int Bares::analizeExpression(Queue<Bares::Token> & _postFix, int & _result) {
	//	Stack to operations 
	Stack <Bares::Token> stackOp;
	Token op1;
	Token op2;
	// While the queue with postfix operations isn't empty
	while(!_postFix.empty()){
		if(_postFix.front().type == TypeSymbol::OPERATOR){ // if the symbol is operator
			if(!stackOp.empty()){ // if the stack isn't empty
				op2 = stackOp.top(); // op2 receive the top of stack
				stackOp.pop(); // the symbol in op2 is removed from stack

				if(!stackOp.empty()){ // if the stack isn't empty
					op1 = stackOp.top(); // op1 receive the top of stack
					stackOp.pop(); // the symbol in op1 is removed from stack

					if(realizeOperation(op1, op2, _postFix.front().symbol)){ // if the operation was computed with successful
						int _op1 = stoi(op1.symbol, nullptr, 10);
						if(_op1 < -32768 || _op1 > 32767){
							errors.push_back({ErrorCode::INVALID_NUMBER_IN_OPERATION, _postFix.front()});
						}
						stackOp.push(op1); // the stack receive the value of operation
					}
					else{ // our queue with errors is incremented with the type of error and the index of error
						errors.push_back({ErrorCode::DIVISION_BY_ZERO, _postFix.front()});
					}
				}else{ // our queue with errors is incremented with the type of error and the index of error
					errors.push_back({ErrorCode::LACKING_OPERAND, _postFix.front()});
				}
			}else{ // our queue with errors is incremented with the type of error and the index of error
				errors.push_back({ErrorCode::LACKING_OPERAND, _postFix.front()});
			}
		}else{ // if the symbol isn't operator, the stack is incremented with the operand
			stackOp.push(_postFix.front());
		}
		_postFix.pop(); // The front symbol of queue is removed
	}
	Token result;
	int first = 0;
	while(!stackOp.empty()){ // verifyng if stack isn't empty
		if(!first){
			result = stackOp.top();
			++first;
		}else{
			result = stackOp.top();
			errors.push_back({ErrorCode::LACKING_OPERATOR, stackOp.top()});
			++first; 
		}
		stackOp.pop();
	}// if the stack has more than on value, the expression is wrong

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

