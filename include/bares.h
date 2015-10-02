#ifndef _BARES_
#define _BARES_

#include <vector>
#include <stack>
#include <queue>

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
		static long calculate(std::string & _word);

	private:
		/**
		*	TODO - Vinícius 
		*	Method that split the expression element by element
		*	
		*	@param _word The expression to be splitted
		*	@return queue<std::string> The queue formed by each element of _word
		**/
		queue<std::string> split(std::string & _word);

		/**
		*	TODO - Vinicius
		*	Method to tranform infix notation to postfix notation
		*	
		*	@param _splittedWord The queue formed by symbols( operands and opertators )
		*	@return queue<std::string> The queue _splittedWord transformed to postfix notation
		**/
		queue<std::string> infixToPostfix(queue<std::string> & _splittedWord);

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
		*	- 3: Tthere is an invalid operand
		*	- 4: There is an invalid operator
		*	- 5: Lacking some operator
		*	- 6: Invalid scope closure
		*	- 7: Opened scope
		*	- 8: Division by zero
		*
		**/
		int analizeExpression(queue<std::string> & _postFix, long & _result);


};

#endif