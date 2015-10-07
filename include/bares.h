#ifndef _BARES_
#define _BARES_
#include <iostream>
#include <string>
#include "stack.h"
#include <queue>
#include "vector.h"
#include "queue.h"

using namespace std;

/**
 * \brief Main class of BARES.
 * \details It has all the necessary operations 
 * to evaluate mathematical expressions following
 * BARES features:
 * - support to +, -, /, *, % operations
 * - accepts negative numbers as valid operands
 * - support to scope definition using parenthesis
 *
 * \version 1.0
 * \authors Vinicius Campos Tinoco Ribeiro, Vitor Rodrigues Greati
 * */
class Bares{

	public:
		/**
		*	\brief Evaluates a given expression. 	
		*	
		*	@param expression An expression to be evaluated.
		*	@param result Receives the result, if no errors ocurred.
		*	@return false, if some error happened, true if there were not errors.
		*	
		*/
		bool evaluate(string & expression, int & result);

	
		/**
		 * \brief Enum that contains codes representing all kinds
		 * of errors that can happen. It's used to select the correct message
		 * to be displayed when the error occur.
		 * */	
		enum class ErrorCode {
			INVALID_NUMBER = 1, 	/**< Thrown when a number out of range is passed.*/
			LACKING_OPERAND,	/**< There is a missing operand.*/
			INVALID_OPERAND,	/**< There is an invalid operand ("a", for example)*/
			INVALID_OPERATOR,	/**< There is an invalid operator ("=", for example)*/
			LACKING_OPERATOR,	/**< There is a missing operator */
			INVALID_SCOPE_CLOSE,	/**< Closing a non-opened scope.*/
			UNCLOSED_SCOPE,		/**< A scope was left open.*/
			DIVISION_BY_ZERO	/**< A division by zero ocurred! */
		};

		/**
		 * \brief Enum that represents possible types of symbols.
		 * It's used in verifications and to classify tokens.
		 * */
		enum class TypeSymbol {
			OPERAND,		/**< It is a valid operand.*/
			OPERATOR,		/**< It is a valid operator.*/
			INVALID_OPERAND,	/**< It is an invalid operand.*/
			INVALID_OPERATOR	/**< It is an invalid operator.*/
		};

		/**
		 * \brief Struct that represents each element inside an expression.
		 * It can be an operand or an operator.
		 * */
		struct Token{
			int column; /**< Where the token starts in the original expression.*/
			TypeSymbol type; /**< Token's type.*/
			string symbol; /**< Token's content.*/
			
			/**
			 * \brief Basic constructor.
			 * */
			Token(){};
			
			/**
			 * \brief Constructor that accepts all attributes
			 * and initializes them. Makes token creation a lot easier.
			 * */
			Token(int _column, TypeSymbol _type, string _symbol = "") : column (_column), type (_type), symbol (_symbol) {};
		};

		/**
		 * \brief This struct is instanciated when an error is detected.
		 * It has a code and the problematic token.
		 * */
		struct Error {
			ErrorCode cod; /**< Error's code.*/
			Token token; /**< The problematic token.*/
			
			/**
			 * \brief Basic constructor.
			 * */
			Error(){};
			
			/**
			 * \brief Constructor that accepts the code and the token,
			 * making error creation a lot easier.
			 * */
			Error(ErrorCode _cod, Token _token) : cod {_cod}, token {_token} {};
			
			/**
			 * \brief Returns error's message based on it's code.
			 * @return Error's message.
			 * */
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
		
		Greati::Vector<Error> errors;/**< List that stores all erros during execution.*/

	public:
		/** 
		 * \brief Print errors.
		 *
		 * @param out Output stream used to print the errors.
		 * @return The output strema.
		 * */
		std::ostream & printErrors(std::ostream & out) {
			out << errors.size() << " errors ocurred!" << endl;
			for (int i = 0; i < errors.size(); ++i)
				out << errors[i].as_string();
			out << endl;
			return out;
		}

		/**
		*	\brief Method that returns the priority order of a given symbol.
		*
		*	@param _symbol The symbol to analize.
		*	@return a number of priority:
		*	- 0: ")"
		*	- 1: "+", "-"
		*	- 2: "*", "/", "%"
		*	- 3: "^"
		*	- 4: "("
		*	- -1: invalid symbol
		**/
		int priority(string _symbol);

		/**
		*	\brief Classify a symbol in operand or operator (valid or invalid).
		*
		*	@param _symbol Symbol to classify.
		*	@return The type of that symbol.
		**/
		TypeSymbol classifySymbol(char _symbol);

		/**
		*	\brief Method that splits the expression element by element,
		*	making tokens.
		*	
		*	@param expression The expression to be splitted / tokenized.
		*	@return Queue<std::Token> The queue formed by all tokens. 
		**/
		void tokenize(string & expression, Queue<Token> & queueToken);

		/**
		*	\brief Method to transform infix notation to postfix notation.
		*	
		*	@param _splittedExpression The queue formed with tokens.
		*	@return The queue _splittedExpression transformed to postfix notation.
		**/
		void infixToPostfix(Queue<Token> & _splittedExpression, Queue<Token> & newQueue);

		/**
		*	\brief Method that analizes the expression stored in _postFix and 
		*	realize the computation, if the expression is ok. 
		*
		*	@param _postFix The queue formed by tokens( operands and operators ) in posfix notation.
		*	@param _result Stores the result. 
		*	@return The result.
		**/
		int analizeExpression(Queue<Token> & _postFix, int & _result);

		/**
		 * \brief Performs a mathematical operation.
		 *
		 * @param op1 First operand.
		 * @param op2 Second operand.
		 * @return if the operation was well succeeded.
		 * */
		bool realizeOperation(Token & op1, Token & op2, string _symbol);

};

#endif
