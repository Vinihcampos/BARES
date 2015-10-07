#ifndef _QUEUE_
#define _QUEUE_

#include <stdexcept>

template <typename Data>
/**
 * \brief Queue implementation.
 * \details Implemented with a simple array, in a circular way.
 * \authors Vinicius Campos Tinoco Ribeiro, Vitor Rodrigues Greati
 * \version 1.0
 * */
class Queue {

	private:
		int head;	/**< Points to the head of the queue.*/
		int tail;	/**< Points to the tail of the queue.*/
		Data *data;	/**< Pointer to data.*/
		int qsize;	/**< Capacity in memory.*/

		static const int DEF_SIZE = 20; /**< Default capacity.*/

		void doubleData();
	public:
		/**
		 * \brief Constructor that initializes all attributes.
		 * */
		Queue(const int _size = DEF_SIZE) : qsize {_size}, head {-1}, tail {-1} {
			if (qsize > 0)
				data = new Data[qsize];
			else
				throw std::invalid_argument("Please provide a size greater than 0.");
		}
		
		/**
		 * \brief Destructor.
		 * */
		~Queue();
		
		/**
		 * \brief Insert new element.
		 * @return true, if inserted.
		 * */
		bool push(const Data & _new);

		/**
		 * \brief Remove element from the queue.
		 * @return a reference to the removed element.
		 * */
		const Data & pop();

		/**
		 * \brief Takes the element at the front of the queue.
		 * @return a reference to the element.
		 * */
		const Data & front() const;

		/**
		 * \brief Takes the logical size of the queue.
		 * @return the logical size.
		 * */
		const int size() const;

		/**
		 * \brief Tells if the queue is empty.
		 * @return true, if empty.
		 * */
		bool empty() const;
};

// Sorry about this
#include "../src/queue.cpp"

#endif
