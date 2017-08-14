#pragma once
#include<iostream>

template <class TYPE>
class Stack
{
public:
	Stack();
	Stack(const int size);
	Stack(Stack<TYPE> const &);

	void push(TYPE&);
	bool pop();
	TYPE* top() const;
	TYPE* topNpop();
	void visualize() const;
	bool isEmpty() const;

	Stack& operator=(Stack<TYPE> const & Other);

	~Stack();
private:
	void copyStack(Stack<TYPE> const & other);
	void resize();
private:
	TYPE** data;
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
	data = new TYPE*[MAX];
}

template<class TYPE>
inline Stack<TYPE>::Stack(const int size)
{
	position = 0;
	MAX = size;
	data = new TYPE*[MAX];
}

template <class TYPE>
void Stack<TYPE>::copyStack(Stack<TYPE> const &other)
{
	if (data != nullptr)
	{
		delete[] data;
	}

	size_t oldPos = other.position;
	position = oldPos;
	data = new TYPE*[oldPos + 1];

	for (int i = 0; i < oldPos; i++)
	{
		data[i] = other.data[i];
	}
}


//
// copy constructor
template <class TYPE>
Stack<TYPE>::Stack(Stack const & oldOne)
{
	copyStack(oldOne);
}
// TODO: test this

template <typename TYPE>
Stack<TYPE>& Stack<TYPE>::operator=(Stack<TYPE> const & Other)
{
	copyStack(Other);
	return *this;
} 
// TODO: Test this

//
// push
template <class TYPE>
void Stack<TYPE>::push(TYPE& newEl)
{
	if (position == MAX)
	{
		resize();
	}

	data[position] = &newEl;
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
TYPE* Stack<TYPE>::top() const
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
TYPE* Stack<TYPE>::topNpop()
{
	// reason for commenting this explained in top()
	// if (isEmpty()) return 0;

	TYPE* returnMePls = top();
	pop();

	return returnMePls;
}

//
// print to cout
template <class TYPE>
void Stack<TYPE>::visualize() const
{

	// for (int i = 0; i < position; i++)
	// {
	// 	std::cout << "[" << i << "]: " << data[i] << std::endl;
	// }
}

//
// isEmpty
template <class TYPE>
bool Stack<TYPE>::isEmpty() const
{
	return position == 0;
	// if (position == 0) return 1;
	// return 0;
}

//
// resize
template <class TYPE>
void Stack<TYPE>::resize()
{
	MAX *= 2;

	TYPE** replacer = new TYPE*[MAX];

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

//////////////////////////////////////////////
// char SPECIALIZATION BELOW
///////////////////////////////////////////

template <>
class Stack<char>
{
public:
	inline Stack();
	inline Stack(const int size);
	inline Stack(Stack<char> const &);

	inline void push(char);
	inline bool pop();
	inline char top() const;
	inline char topNpop();
	inline void visualize() const;
	inline bool isEmpty() const;

	inline Stack& operator=(Stack<char> const & Other);

	inline ~Stack();
private:
	inline void copyStack(Stack<char> const & other);
	inline void resize();
private:
	char* data;
	int position;
	int MAX = 1;
};



///////////////////////
// CLASS INTERFACE ENDS HERE
//////////////////////



Stack<char>::Stack()
{
	position = 0;
	data = new char[MAX];
}

Stack<char>::Stack(const int size)
{
	position = 0;
	MAX = size;
	data = new char[MAX];
}

void Stack<char>::copyStack(Stack<char> const &other)
{
	if (data != nullptr)
	{
		delete[] data;
	}

	size_t oldPos = other.position;
	position = oldPos;
	data = new char[oldPos + 1];

	for (unsigned int i = 0; i < oldPos; i++)
	{
		data[i] = other.data[i];
	}
}


//
// copy constructor
Stack<char>::Stack(Stack<char> const & oldOne)
{
	copyStack(oldOne);
}
// TODO: test this

Stack<char>& Stack<char>::operator=(Stack<char> const & Other)
{
	copyStack(Other);
	return *this;
}
// TODO: Test this

//
// push
void Stack<char>::push(char newEl)
{
	if (position == MAX)
	{
		resize();
	}

	data[position] = newEl;
	position++;
}

//
// pops the highest element
// / returns 'true' or 'false' depending on if there was a popped element
bool Stack<char>::pop()
{
	// i'd rather skip this because every time I try popping a stack in the main program I first check whether it's empty or not
	// and on top of that if i dont check that outside, I'll then have to check whether
	// the pointer is null or not, e.g. an extra check
	
	//if (isEmpty())
	//	return 0;

	position--;
	return 1;

}

//
// / returns the value of the last inserted element WITHOUT POPPING it
char Stack<char>::top() const
{
	// i'd rather skip this because every time I try popping a stack in the main program I first check whether it's empty or not
	// and on top of that if i dont check that outside, I'll then have to check whether
	// the pointer is null or not, e.g. an extra check
	// if (isEmpty()) return nullptr;

	return data[position - 1];
}

//
// top + pop
char Stack<char>::topNpop()
{
	// reason for commenting this explained in top()
	// if (isEmpty()) return 0;

	char returnMePls = top();
	pop();

	return returnMePls;
}

//
// print to cout
void Stack<char>::visualize() const
{

	for (int i = 0; i < position; i++)
	{
		std::cout << "[" << i << "]: " << data[i] << std::endl;
	}
}

//
// isEmpty
bool Stack<char>::isEmpty() const
{
	return position == 0;
	// if (position == 0) return 1;
	// return 0;
}

//
// resize
void Stack<char>::resize()
{
	MAX *= 2;

	char* replacer = new char[MAX];

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

Stack<char>::~Stack()
{
	if (data != nullptr)
	{
		delete[] data;
	}
}