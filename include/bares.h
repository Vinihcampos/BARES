#ifndef _BARES_
#define _BARES_

#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include <queue>

using namespace std;

class Bares{

	public:
		/**
		*	TODO - Vitor 
		*	
		*	General method that use other private methods to realize 
		*	the computation of expression
		*	
		*	@param _word An expression to be evaluated
		*	@return the result of expression
		*	
		**/
		bool evaluate(string & expression, int & resultado);

		
		enum class ErrorCode {
			INVALID_NUMBER = 1, 	// calculation
			LACKING_OPERAND,	// calculation
			INVALID_OPERAND,	// tokenize
			INVALID_OPERATOR,	// tokenize
			LACKING_OPERATOR,	// calculation
			INVALID_SCOPE_CLOSE,	// calculation or infix
			UNCLOSED_SCOPE,		// calculation or infix
			DIVISION_BY_ZERO	// calculation
		};

		enum class TypeSymbol {
			OPERAND,
			OPERATOR,
			INVALID_OPERAND,
			INVALID_OPERATOR
		};

		struct Token{
			int column;
			TypeSymbol type;
			string symbol;
			Token(){};
			Token(int _column, TypeSymbol _type, string _symbol = "") : column (_column), type (_type), symbol (_symbol) {};
		};

		struct Error {
			ErrorCode cod;
			Token token;
			Error(ErrorCode _cod, Token _token) : cod {_cod}, token {_token} {};
			string as_string() {
				string msg;
				msg += "Error at column " + std::to_string(token.column) + ": ";
				switch(cod) {
					case ErrorCode::INVALID_NUMBER:
						msg += "Number constant out of range.";
						break;
					case ErrorCode::LACKING_OPERAND:
						msg += "Valid operand lacking.";
						break;
					case ErrorCode::INVALID_OPERAND:
						msg += "Invalid operand.";
						break;
					case ErrorCode::LACKING_OPERATOR:
						msg += "Valid operator lacking.";
						break;
					case ErrorCode::INVALID_OPERATOR:
						msg += "Invalid operator.";
						break;
					case ErrorCode::INVALID_SCOPE_CLOSE:
						msg += "Invalid scope closing.";
						break;
					case ErrorCode::UNCLOSED_SCOPE:
						msg += "Unclosed scope.";
						break;
					case ErrorCode::DIVISION_BY_ZERO:
						msg += "Division by zero!";
						break;
					default:
						msg += "Unknown error.";
				}
				msg += "\n";
				return msg;
			}
		};

		vector<Error> errors;

	public:
		/** 
		 * Print errors.
		 *
		 * */
		std::ostream & printErrors(std::ostream & out) {
			out << errors.size() << " errors ocurred!" << endl;
			for (Error e : errors) 
				out << e.as_string();
			return out;
		}



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
		TypeSymbol classifySymbol(char _symbol);

		/**
		*	TODO - Vinícius 
		*	Method that split the expression element by element
		*	
		*	@param _word The expression to be splitted
		*	@return queue<std::string> The queue formed by each element of _word
		**/
		void tokenize(string & expression, queue<Token> & queueToken);

		/**
		*	TODO - Vinicius
		*	Method to tranform infix notation to postfix notation
		*	
		*	@param _splittedExpression The queue formed by symbols( operands and opertators )
		*	@return queue<std::string> The queue _splittedExpression transformed to postfix notation
		**/
		void infixToPostfix(queue<Token> & _splittedExpression, queue<Token> & newQueue);

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
		int analizeExpression(queue<Token> & _postFix, int & _result);

		bool realizeOperation(Token & op1, Token & op2, string _symbol);

};

#endif
