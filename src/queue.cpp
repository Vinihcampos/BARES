#include <algorithm>
#include "queue.h"
#include <stdexcept>

template<typename Data>
Queue<Data>::~Queue() {
	delete [] data;
}

template<typename Data>
bool Queue<Data>::push(const Data & _new) {
	int nextPosition = (head + 1) % qsize;
	if (nextPosition == tail) {
		doubleData();
		nextPosition = (head + 1) % qsize;
	}
	head = nextPosition;
	data[head] = _new;
	if (tail == -1) 
		tail = 0;
	return true;
}

template<typename Data>
const Data & Queue<Data>::pop() {
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
const Data & Queue<Data>::front() const {
	if (tail != -1) 
		return data[tail];
	else
		throw std::runtime_error("Queue is empty.");
}

template<typename Data>
bool Queue<Data>::empty() const {
	return (tail == -1); 
}

template<typename Data>
const int Queue<Data>::size() const {
	if (tail == -1) return 0;
	if (head >= tail) return head - tail + 1;
	else return qsize - (tail - head);
}

template <typename Data>
void Queue<Data>::doubleData() {
	Data * _new = new Data[qsize * 2];
	for (auto i(head), j(0); i < qsize; ++j, ++i){
		_new[j] = this->data[i];
	}
	for(auto i(0), j(qsize); i <= tail; ++i, ++j){
		_new[j] = this->data[i];
	}
	delete [] data;
	this->data = _new;
	head = 0;
	tail = qsize;
	qsize *= 2;	
}