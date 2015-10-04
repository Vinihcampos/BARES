#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "bares.h"

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
	/*for (int i = 0; i < expression.size(); ++i) {*/
		// ignorable
		if (expression[i] == ' ') { 
			++i;
			continue;
		}
		// check the type
		TypeSymbol type = classifySymbol(expression[i]);
		
		token = new Bares::Token {i, type};
		
		if (type == TypeSymbol::OPERAND) {
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

//	Infix to postfix method
//	Verifyng errors:
//	- 1: Numerical constant is invalid
//	- 6: Invalid scope closure
//	- 7: Opened scope	
void Bares::infixToPostfix(queue<Bares::Token> & _splittedExpression, queue<Bares::Token> & newQueue){
/*	stack<Bares::Token> stack;
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
*/
}

int Bares::analizeExpression(queue<Token> & _postFix, long & _result) {
/*	Token curSymb; 		// current symbol
	int op1, op2;		// operands
	int res = 0;		// answer
	stack<int> stackOp; 	// stack of operands

	// there are symbols to be analyzed
	while (!_postFix.empty()) {
		curSymb = _postFix.front();	
		
		if (curSymb.l


		_postFix.pop();
	}
*/
	return 0; // stub
}









