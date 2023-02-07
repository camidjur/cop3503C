#pragma once
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABQ {
private:
	unsigned int maximumCapacity = 0;
	unsigned int size = 0;
	const float scaleFactor = 2.0f;
	T* pointerArray;
public:
	ABQ() {
		maximumCapacity = 1;
		size = 0;
		pointerArray = new T[maximumCapacity];
	}
	ABQ(int capacity) {
		size = 0;
		maximumCapacity = capacity;
		pointerArray = new T[maximumCapacity];
	}
	ABQ(const ABQ& d) {
		delete[] pointerArray;

		size = d.size;
		maximumCapacity = d.capacity;

		for (unsigned int i = 0; i < d.size; i++) {
			pointerArray[i] = d[i];
		}

	}
	ABQ& operator=(const ABQ& d) {
		delete[] pointerArray;

		size = d.size;
		maximumCapacity = d.capacity;

		for (unsigned int i = 0; i < d.size; i++) {
			pointerArray[i] = d[i];
		}
		return *this;
	}
	~ABQ() {
		delete[] pointerArray;
	}
	void enqueue(T data) {

		if (size == maximumCapacity) {
			maximumCapacity *= scaleFactor;

			T* tempPointer = new T[maximumCapacity];
			for (unsigned int i = 0; i < size; i++) {
				tempPointer[i] = pointerArray[i];
			}
			delete[] pointerArray;
			pointerArray = tempPointer;

			tempPointer = nullptr;
		}

		pointerArray[size] = data;
		++size;

	}
	T dequeue() {

		if (size == 0) {
			throw runtime_error("The stack is empty");
		}
		T someValue = pointerArray[0];

		 if ((size - 1) / float(maximumCapacity) < (1 / scaleFactor)) {
			maximumCapacity = maximumCapacity / scaleFactor;

			T* tempPointer = new T[maximumCapacity];
			for (unsigned int i = 0; i < maximumCapacity; i++) {
				tempPointer[i] = pointerArray[i+1];
			}
			delete[] pointerArray;
			pointerArray = tempPointer;

			tempPointer = nullptr;
		 }
		 else {
			 T* tempPointer = new T[maximumCapacity];
			 for (unsigned int i = 0; i < maximumCapacity; i++) {
				 tempPointer[i] = pointerArray[i+1];
			 }
			 delete[] pointerArray;
			 pointerArray = tempPointer;

			 tempPointer = nullptr;
		 }
		--size;
		return someValue;

	}
	T peek() {
		if (size == 0) {
			throw runtime_error("The stack is empty");
		}
		else {
			return pointerArray[0];
		}
	}
	unsigned int getSize() {
		return size;
	}
	unsigned int getMaxCapacity() {
		return maximumCapacity;
	}
	T* getData() {
		return pointerArray;
	}



};