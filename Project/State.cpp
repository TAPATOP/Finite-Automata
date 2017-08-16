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

#include "State.h"



State::State(int transitionCharacter, State* first, State* second)
{
	this->transitionCharacter = transitionCharacter;
	this->next = first;
	this->next2 = second;
}


void State::process_symbol(char c, LinkedList<State*>* listForEnqueue, int listID)
{
	if (can_match_symbol(c))
	{
		next->get_enqueued(listForEnqueue, listID);
	}
	// if this has the same address as next2, then this is the state of \\e, and as
	// we know, the empty string matches everything
	else if (this == this->next2)
	{
		get_enqueued(listForEnqueue, listID);
	}
		
}


void State::get_enqueued(LinkedList<State*>* listForEnqueue, int listID)
{
	// checks if this state has already been processed
	if (this == nullptr || this->listID == listID) return;

	// marks the state as "processed"
	this->listID = listID;

	// if this state is a split -> adds both it's children
	if (this->transitionCharacter == StateTransitionCodes::Split)
	{
		if (next2 == this)
		{
			listForEnqueue->enqueue(this);
			next->get_enqueued(listForEnqueue, listID);
		}
		else
		{
			next->get_enqueued(listForEnqueue, listID);
			next2->get_enqueued(listForEnqueue, listID);
		}
	}
	else
	{
		listForEnqueue->enqueue(this);
	}
}


void State::reset_states()
{
	listID = -1;
	if (next2 != nullptr && next2->listID != -1)
	{
		next2->reset_states();
	}
	if (next != nullptr && next->listID != -1)
	{
		next->reset_states();
	}
}


void State::delete_states()
{
	//if (next2 != nullptr && next2 != this)
	//{
	//	next2->delete_states();
	//}
	//if (next != nullptr)
	//{
	//	next->delete_states();
	//}
	//delete this;
}


State::~State()
{
}


int State::symbol_type(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return StateTransitionCodes::Letter;
	}
	if (c >= '0' && c <= '9')
	{
		return StateTransitionCodes::Digit;
	}
	if (c == ' ' || c == '\t')
	{
		return StateTransitionCodes::Space;
	}
	return 0;
}


bool State::can_match_symbol(char c)
{
	int cType = symbol_type(c);

	if (get_state_transition_value_by_char(c) == this->transitionCharacter) return true;
	if (cType == transitionCharacter) return true;

	return false;
}


int get_state_transition_value_by_char(char c)
{
	switch (c)
	{
	case 'A':
		return StateTransitionCodes::Letter;
	case 'D':
		return StateTransitionCodes::Digit;
	case 'S':
		return StateTransitionCodes::Space;
	case 'E':
		return StateTransitionCodes::Empty;
	default:
		return c;
	}
}
