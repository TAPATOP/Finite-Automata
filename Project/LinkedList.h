#pragma once
#include<iostream>

// stores the objects by saving their values by value
template <class T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(T*);

	void enqueue(T*);
	T* dequeue();
	void concatenate_to_me(LinkedList<T>*& followingList);

	bool is_empty();

	void print_all();
	
	~LinkedList();
private:
	struct Node
	{
		Node(T* data)
		{
			this->data = data;
			next = nullptr;
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
	first = nullptr;
	last = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(T* val)
{
	first = new Node(val);

	last = first;
}

template <class T>
void LinkedList<T>::enqueue(T* addMe)
{
	Node* newNode = new Node(addMe);
	if (last != nullptr)
	{
		last->next = newNode;
	}

	last = newNode;
	

	if (first == nullptr)
	{
		first = last;
	}
}

template<class T>
T* LinkedList<T>::dequeue()
{
	T* returnedData = first->data;
	Node* nextNode = first->next;

	delete first;

	first = nextNode;

	return returnedData;
}

// makes the last node of this list point to the first node of the followingList
// !! WARNING !!
// This makes the followingList's pointer nullptr in order to prevent memory coruption when deleting
template<class T>
void LinkedList<T>::concatenate_to_me(LinkedList<T>*& followingList)
{
	this->last->next = followingList->first;
	this->last = followingList->last;

	followingList = nullptr;
}

template<class T>
inline bool LinkedList<T>::is_empty()
{
	return first == nullptr;
}

// prints all the entries in the list;
// the data must have a predefined << operator
template <class T>
void LinkedList<T>::print_all()
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
	Node* current = first;

	while(current != nullptr)
	{
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
}
