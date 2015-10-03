#ifndef _BARES_
#define _BARES_

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Bares{

	public:
		/**
		*	TODO - Vitor 
		*	
		*	General method that use other private methods to realize 
		*	the computation of excpression
		*	
		*	@param _word An expression to be evaluated
		*	@return the result of expression
		*	
		**/
		static long calculate(string & _expression);

		struct Node{
			string symbol;
			int index;
			Node(string _symbol, int _index) : symbol {_symbol}, index {_index}{};
		};

		queue< pair < string, int > > errors;

	public:
		/**
		*	TODO - Vinícius
		*	Method that returns the priority of the symbol
		*
		*	@param _symbol The symbol to analize
		*	@return a number of priority:
		*	- 1: ()
		*	- 2: -(unary)
		*	- 3: ^
		*	- 4: * / %
		*	- 5: + -
		**/
		int priority(string _symbol);

		/**
		*	TODO - Vinícius
		*	Method that returns if the symbol is valid
		*
		*	@param _symbol The symbol to analize
		*	@return true if is a valid symbol, false otherwise 
		**/
		int validSymbol(char _symbol);

		/**
		*	TODO - Vinícius 
		*	Method that split the expression element by element
		*	
		*	@param _word The expression to be splitted
		*	@return queue<std::string> The queue formed by each element of _word
		**/
		void split(string & _expression, queue<Node> & queue);

		/**
		*	TODO - Vinicius
		*	Method to tranform infix notation to postfix notation
		*	
		*	@param _splittedExpression The queue formed by symbols( operands and opertators )
		*	@return queue<std::string> The queue _splittedExpression transformed to postfix notation
		**/
		void infixToPostfix(queue<Node> & _splittedExpression, queue<Node> & newQueue);

		/**
		*	TODO Vitor
		*	Method that analize the expression stored in _postFix and 
		*	realize the computation, if the expression is ok. 
		*
		*	@param _postFix The queue formed by symbols( operands and opertators ) in postfix notation
		*	@param _result The variable to store the coputation of expression.
		*	@return a number of that represent the state of expression:
		*	- 0: If the coputation is ok.
		*	- 1: Numerical constant is invalid.
		*	- 2: Lacking some operand 
		*	- 3: There is an invalid operand
		*	- 4: There is an invalid operator
		*	- 5: Lacking some operator
		*	- 6: Invalid scope closure
		*	- 7: Opened scope
		*	- 8: Division by zero
		*
		**/
		int analizeExpression(queue<Node> & _postFix, long & _result);

	

};

#endif