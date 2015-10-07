#ifndef _STACKIMPL_
#define _STACKIMPL_

#include "AbsStack.h"

template <typename Object>
/**
 * \brief Implementation of a stack.
 * \details Implemented with a simple array, dinamically reallocated when necessary.
 * \authors Vitor Rodrigues Greati, Vinicius Campos Tinoco Ribeiro
 * \version 1.0
 * */
class Stack : public AbsStack<Object> {

	private:
		static const int DEF_CAPACITY = 50; 	/**< Default capacity.*/
		int capacity;				/**< Size in memory.*/
		int topIndex;				/**< Points to the top of the stack.*/
		Object *data;				/**< Pointer to data.*/
	
		void doubleData(); 			/**< Doubles the capacity when necessary.*/
			
	public:
		/**
		 * \brief Constructor that initializes all attributes.
		 * */
		Stack() : AbsStack<Object>(),	
			  capacity {DEF_CAPACITY},
	       		  topIndex {0},	
			  data { new Object[capacity] } {};
		
		/**
		 * \brief Destructor.
		 * */
		~Stack() { delete [] data; };

		/**
		 * \brief Insert element.
		 * */
		void push (const Object & x);

		/**
		 * \brief Remove element.
		 * @return A reference to the removed data.
		 * */
		const Object & pop();

		/**
		 * \brief Takes the element at the top.
		 * @return A reference to the element.
		 * */
		const Object & top() const;

		/**
		 * \brief Tells if the stack is empty.
		 * @return true, if it's empty.
		 * */
		bool empty() const;

		/**
		 * \brief Clear stack.
		 * */
		void clear();
};

// Sorry about this
#include "../src/stack.inl"

#endif
