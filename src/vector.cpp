#include "vector.h"
#include <stdexcept>
#include <initializer_list>

namespace Greati {

	template <typename T>
	void Vector<T>::doubleData() {
		T * _new = new T[this->vecCapacity * 2];
		for (auto i(0); i < this->vecSize; ++i)
			_new[i] = this->vecData[i];
		delete [] this->vecData;
		this->vecData = _new;
		this->vecCapacity *= 2;	
	}

	template<typename T>
	Vector<T>::~Vector() {
		delete [] vecData;
	}

	template<typename T>
	int Vector<T>::size(void) const {
		return vecSize;
	}

	template<typename T>
	void Vector<T>::fill(const T & value) {
		for (int i = 0; i < vecSize; ++i)
			*(vecData + i) = value;
	}

	template<typename T>
	void Vector<T>::push_back(const T & value) {
		if (vecSize == vecCapacity) 
			doubleData();
		*(vecData + vecSize) = value;
		vecSize++;
	}

	template<typename T>
	T& Vector<T>::operator[](int index) {
		if (index < 0 && index > vecCapacity - 1)
			throw std::out_of_range("Error: Index out of range.");
		return *(vecData + index);
	}
	
	template<typename T>
	const T Vector<T>::operator[](int index) const {
		if (index < 0 && index > vecCapacity - 1)
			throw std::out_of_range("Error: Index out of range.");
		return *(vecData + index);
	}

	template<typename T>
	bool Vector<T>::operator==(const Vector & rhs) const {
		if (this->vecCapacity != rhs.vecCapacity) return false;
		for (int i = 0; i < this->vecSize; ++i)
			if (*(this->vecData + i) != *(rhs.vecData + i)) return false;
		return true;
	}
	
	template<typename T>
	const Vector<T> & Vector<T>::operator=(const Vector & rhs) {
		if (this != &rhs) {
			if (rhs.vecCapacity != (this->vecCapacity)) {
				delete [] (this->vecData);
				(this->vecData) = new T[rhs.vecCapacity];
				this->vecCapacity = rhs.vecCapacity;
			}
			for (int i = 0; i < rhs.vecSize; ++i)
				*((this->vecData) + i) = *(rhs.vecData + i); 
		}
		return *this;
	}

	template<typename T>
	const Vector<T> & Vector<T>::operator=(const initializer_list<T> & rhs) {
		if (rhs.size() != (this->vecCapacity)){
			delete [] (this->vecData);
			this->vecData = new T[rhs.size()];
			this->vecCapacity = rhs.size();	
		}
		typename initializer_list<T>::iterator it;
		it = rhs.begin();
		for (int i = 0; it != rhs.end(); ++it, i++)
			*(this->vecData + i) = (*it);

		return *this;
	} 
	
}
