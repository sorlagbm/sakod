#pragma once
#include "StackExceptions.h"

template<class T>
class qstack{

public:

	static constexpr size_t K = 25;

private:

	T stack[K];
	int top;

public:

	qstack() : top(-1) {}

	void push(const T& item) {

		if (top == K - 1) throw OverflowException();
		else {

			top += 1;
			stack[top] = item;

		}

	}
	T pop() {

		T temp;

		if (top == -1) throw EmptyListException();
		else {

			temp = stack[top];
			top -= 1;
			return temp;

		}

	}
	void clear() { top = -1; }

	T head() const {

		if (top == -1) throw EmptyListException();
		else return stack[top];

	}

	bool isEmpty() { return top == -1; }
	bool isFull() { return top == K - 1; }

};

