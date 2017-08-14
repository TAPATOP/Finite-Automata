#pragma once
#include<iostream>

template <class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(T*);

	void enqueue(T*);
	T* dequeue();

	void printAll();
	
	~LinkedList();
private:
	struct Node
	{
		Node()
		{
			next = nullptr;
		}
		~Node()
		{
			if (next != nullptr)
			{
				delete next;
			}
		}
		T* data;
		Node* next;
	};

	Node* first; // first node of the list
	Node* last; // this is the address of the last node in the list, WHICH IS UNINITIALIZED
};

template <class T>
LinkedList<T>::LinkedList()
{
	first = new Node();
	last = first;
}

template <class T>
LinkedList<T>::LinkedList(T* val)
{
	first = new Node();
	first->data = val;

	last = new Node();
	first->next = last;
}

template <class T>
void LinkedList<T>::enqueue(T* addMe)
{
	last->data = addMe;
	Node* newNode = new Node();
	last->next = newNode;
	last = newNode;
}

template<class T>
inline T * LinkedList<T>::dequeue()
{
	Node* returnedOne = first;
	first = first->next;

	return returnedOne->data;
}

// prints all the entries in the list;
// the data must have a predefined << operator
template <class T>
void LinkedList<T>::printAll()
{
	if (first == last)
	{
		return;
	}
	Node current = first;
	while (current->next != nullptr)
	{
		std::cout << current->data << std::endl;
		current = current->next;
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{
	// recursive delete
	if (first != nullptr) delete first;

	// non- recursive delete; make sure you fix ~Node() before you uncomment this

	//resetCurrent();
	//while(current->next != nullptr)
	//{
	//	Node* nextNode = current->next;
	//	delete current;
	//	current = nextNode;
	//}
}
