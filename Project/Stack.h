#pragma once
#include<iostream>

template <class TYPE>
class Stack
{
public:
	Stack();
	Stack(const int size);
	Stack(Stack<TYPE> &);

	void push(TYPE);
	bool pop();
	TYPE top() const;
	TYPE topNpop();
	void visualize() const;
	bool isEmpty() const;

	Stack& operator=(Stack<TYPE>& Other);

	~Stack();
private:
	void copyStack(Stack<TYPE>& other);
	void resize();
private:
	TYPE* data;
	int position;
	int MAX = 1;
};



///////////////////////
// CLASS INTERFACE ENDS HERE
//////////////////////



template <class TYPE>
Stack<TYPE>::Stack()
{
	position = 0;
	data = new TYPE[MAX];
}

template<class TYPE>
Stack<TYPE>::Stack(const int size)
{
	position = 0;
	MAX = size;
	data = new TYPE[MAX];
}

template <class TYPE>
void Stack<TYPE>::copyStack(Stack<TYPE> &other)
{
	if (data != nullptr)
	{
		delete[] data;
	}

	size_t oldPos = other.position;
	position = oldPos;
	data = new TYPE[oldPos + 1];

	for (unsigned int i = 0; i < oldPos; i++)
	{
		data[i] = other.data[i];
	}
}


//
// copy constructor
template <class TYPE>
Stack<TYPE>::Stack(Stack& oldOne)
{
	copyStack(oldOne);
}

template <typename TYPE>
Stack<TYPE>& Stack<TYPE>::operator=(Stack<TYPE>& Other)
{
	copyStack(Other);
	return *this;
} 

//
// push
template <class TYPE>
void Stack<TYPE>::push(TYPE newEl)
{
	if (position == MAX)
	{
		resize();
	}

	data[position] = newEl;
	position++;
}

//
// pop
template <class TYPE>
bool Stack<TYPE>::pop()
{
	if (isEmpty())
		return 0;

	position--;
	return 1;

}

//
// top
template <class TYPE>
TYPE Stack<TYPE>::top() const
{
	// i'd rather skip this because every time I try popping a stack I first check whether it's empty or not
	// and on top of that if i dont check that outside, I'll then have to check whether
	// the pointer is null or not, e.g. an extra check
	// if (isEmpty()) return nullptr;

	return data[position - 1];
}

//
// top + pop
template <class TYPE>
TYPE Stack<TYPE>::topNpop()
{
	// reason for commenting this explained in top()
	// if (isEmpty()) return 0;

	TYPE returnMePls = top();
	pop();

	return returnMePls;
}

//
// print to cout
template <class TYPE>
void Stack<TYPE>::visualize() const
{
	for (int i = 0; i < position; i++)
	{
		std::cout << "[" << i << "]: " << data[i] << std::endl;
	}
}

//
// checks if all the data has been popped or if there has simply never been any data
template <class TYPE>
bool Stack<TYPE>::isEmpty() const
{
	return position == 0;
	// if (position == 0) return 1;
	// return 0;
}

//
// copies the stack data into an array of twice the current size
template <class TYPE>
void Stack<TYPE>::resize()
{
	MAX *= 2;

	TYPE* replacer = new TYPE[MAX];

	for (int i = 0; i < position; i++)
	{
		replacer[i] = data[i];
	}

	if (data != nullptr)
	{
		delete[] data;
	}

	data = replacer;
}

template <class TYPE>
Stack<TYPE>::~Stack()
{
	if (data != nullptr)
	{
		delete[] data;
	}
}
