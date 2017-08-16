/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 0
* @compiler VC
*
*/

#pragma once
#include<iostream>

// stores the objects by saving their values by value
// e.g. if you want to store a big object, you should use LinkedList<Object*>
template <class T>
class LinkedList
{
public:
	struct Node
	{
		Node(T data)
		{
			this->data = data;
			next = nullptr;
		}
		T data;
		Node* next;
	};
public:
	LinkedList();
	LinkedList(T);

	void setFirst(Node* first);
	void setLast(Node* last);

	Node* getFirst();
	Node* getLast();

	void enqueue(T);
	T dequeue();
	void concatenate_with(LinkedList<T>*& followingList);
	Node* grant_access_to_first();

	bool is_empty();

	void print_all();

	~LinkedList();
private:

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
LinkedList<T>::LinkedList(T val)
{
	first = new Node(val);

	last = first;
}

template<class T>
inline void LinkedList<T>::setFirst(Node * first)
{
	this->first = first;
}

template<class T>
inline void LinkedList<T>::setLast(Node * last)
{
	this->last = last;
}

template<class T>
inline typename LinkedList<T>::Node * LinkedList<T>::getFirst()
{
	return first;
}

template<class T>
inline typename LinkedList<T>::Node * LinkedList<T>::getLast()
{
	return last;
}

template <class T>
void LinkedList<T>::enqueue(T addMe)
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
T LinkedList<T>::dequeue()
{
	T returnedData = first->data;
	Node* nextNode = first->next;

	if (first == last)
	{
		last = nullptr;
	}

	delete first;

	first = nextNode;

	return returnedData;
}

// makes the last node of this list point to the first node of the followingList;
// e.g. connects the end of our list with the beginning of the following one
// !! WARNING !!
// This makes the followingList's pointer nullptr in order to prevent memory corruption when deleting
// and then deletes it : )
template<class T>
void LinkedList<T>::concatenate_with(LinkedList<T>*& followingList)
{
	this->last->next = followingList->first;
	this->last = followingList->last;

	followingList = nullptr;
	delete followingList;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::grant_access_to_first()
{
	return first;
}

template<class T>
bool LinkedList<T>::is_empty()
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
