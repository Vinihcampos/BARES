#include <algorithm>
#include "queue.h"
#include <stdexcept>

template<typename Data>
queue<Data>::~queue() {
	delete [] data;
}

template<typename Data>
bool queue<Data>::push(const Data & _new) {
	int nextPosition = (head + 1) % qsize;
	if (nextPosition != tail) {
		head = nextPosition;
		data[head] = _new;
		if (tail == -1) 
			tail = 0;
		return true;
	} else false; 
}

template<typename Data>
const Data & queue<Data>::pop() {
	if (tail != -1) {
	        int returnIndex = tail;	
		if (head == tail)
			head = tail = -1;
		else
			tail = (tail + 1) % qsize;
		return data[returnIndex];
	} else throw std::runtime_error("Queue is empty.");
}

template<typename Data>
const Data & queue<Data>::front() const {
	if (tail != -1) 
		return data[tail];
	else
		throw std::runtime_error("Queue is empty.");
}

template<typename Data>
bool queue<Data>::empty() const {
	return (tail == -1); 
}

template<typename Data>
const int queue<Data>::size() const {
	if (tail == -1) return 0;
	if (head >= tail) return head - tail + 1;
	else return qsize - (tail - head);
}
