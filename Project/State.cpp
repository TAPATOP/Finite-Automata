#include "State.h"



State::State(int transitionCharacter, State* first, State* second)
{
	this->transitionCharacter = transitionCharacter;
	this->next = first;
	this->next2 = second;
}

bool State::can_match_symbol(char c, LinkedList<State*>* stateList, int listID)
{
	int symbolType = symbol_type(c);



	return 0;
}


void State::get_enqueued(LinkedList<State*>* stateList, int listID)
{
	// checks if this state is already queued
	if (this->listID == listID) return;

	// enqueues this state
	this->listID = listID;
	stateList->enqueue(this);

	// if this state is a split -> adds both it's children
	if (this->transitionCharacter == StateTransitionCodes::Split)
	{
		next->get_enqueued(stateList, listID);
		next2->get_enqueued(stateList, listID);
	}
}

State::~State()
{
}

// 0 -> none of the below
// 1 -> letter
// 2 -> digit
int State::symbol_type(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return 1;
	}
	if (c >= '0' && c <= '9')
	{
		return 2;
	}
	return 0;
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
