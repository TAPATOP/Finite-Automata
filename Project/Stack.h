#pragma once
#include<iostream>

template <class TYPE>
class Stack
{
public:
	Stack();
	Stack(const int size);
	Stack(Stack&);

	void push(TYPE);
	bool pop();
	TYPE top();
	TYPE topNpop();
	void visualize() const;
	bool isEmpty();

	Stack& operator=(Stack const & Other);

	~Stack();

private:
	TYPE* data;
	int position;
	int MAX = 1;
	void copyStack(Stack<TYPE> const & other);
	void resize();
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
inline Stack<TYPE>::Stack(const int size)
{
	position = 0;
	MAX = size;
	data = new TYPE[MAX];
}

template <class TYPE>
void Stack<TYPE>::copyStack(Stack<TYPE> const &other)
{
	delete[] data;
	size_t oldPos = other.position;
	position = oldPos;
	data = new TYPE[oldPos + 1];

	for (int i = 0; i < oldPos; i++)
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
Stack<TYPE>& Stack<TYPE>::operator=(Stack<TYPE> const & Other)
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
TYPE Stack<TYPE>::top()
{
	//	if (isEmpty()) return 0;

	return data[position - 1];
}

//
// top + pop
template <class TYPE>
TYPE Stack<TYPE>::topNpop()
{
	if (isEmpty()) return 0;

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
// isEmpty
template <class TYPE>
bool Stack<TYPE>::isEmpty()
{
	if (position == 0) return 1;
	return 0;
}

//
// resize
template <class TYPE>
void Stack<TYPE>::resize()
{
	MAX *= 2;

	TYPE* replacer = new TYPE[MAX];

	for (int i = 0; i < position; i++)
	{
		replacer[i] = data[i];
	}

	delete[] data;
	data = replacer;
}

template <class TYPE>
Stack<TYPE>::~Stack()
{
	delete[] data;
}
