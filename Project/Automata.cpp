#include "Automata.h"



Automata::Automata()
{
	startState = nullptr;
	outStatesList = nullptr;
}

Automata::Automata(State* startState, LinkedList<State*>* outStatesList)
{
	this->startState = startState;
	this->outStatesList = outStatesList;
}

// makes all the outStates of the current Automata point towards
// the beginning of the followingAutomata and makes the followingAutomata's
// outStatesList the new outArrowList of the current Automata by copying it's address
// !!! WARNING !!!
// Destroys the followingAutomata because you should not be able to access it directly after
// the concatenation has taken place( since, technically, you have >merged< two Automatas into one
void Automata::concatenate_with(Automata* followingAutomata)
{
	LinkedList<State*>::Node* node = this->outStatesList->grant_access_to_first();
	State* state = nullptr;

	State* followingStart = followingAutomata->startState;

	while (node != nullptr)
	{
		state = node->data;
		state->next = followingStart;
	
		node = node->next;
	}

	this->outStatesList = followingAutomata->outStatesList;
	delete followingAutomata;
}

Automata::~Automata()
{
}
