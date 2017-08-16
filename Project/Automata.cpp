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

void Automata::concatenate_with(Automata* followingAutomata)
{
	// gets the ending nodes of this list
	LinkedList<State*>::Node* node = this->outStatesList->grant_access_to_first();
	State* state = nullptr;

	State* followingStart = followingAutomata->startState;

	// connects the ending nodes of this list to the starting state of the followingAutomata
	while (node != nullptr)
	{
		state = node->data;
		state->next = followingStart;
	
		node = node->next;
	}

	// sets this Automata's outStatesList to the outStatesList of the followingAutomata
	this->outStatesList = followingAutomata->outStatesList;

	// deletes the followingAutomata, since it doesn't exist on it's own anymore
	delete followingAutomata;
}

void Automata::iterate()
{
	// creates the new state
	State* newState = new State(StateTransitionCodes::Split, nullptr, this->startState);

	State* state = nullptr;

	// dequeues and connects all the ending states of the Automata with the newState
	while (!outStatesList->is_empty())
	{
		state = outStatesList->dequeue();
		state->next = newState;
	}

	// makes the startState of this Automata the newState
	startState = newState;

	// enqueues the newState in the ending nodes list
	outStatesList->enqueue(newState);
}

void Automata::alternate_with(Automata* alternateAutomata)
{
	// create the new state
	State* newState = new State(StateTransitionCodes::Split, this->startState, alternateAutomata->startState);

	// set the current automata's start state to the new one
	startState = newState;

	// concatenate the list of ending nodes of the two automatas
	this->outStatesList->concatenate_with(alternateAutomata->outStatesList);

	// delete the last automata, since this operation creates one automata out of two other
	delete alternateAutomata;
}

void Automata::finalize()
{
	State* matchState = new State(StateTransitionCodes::Match);

	LinkedList<State*>::Node* node = outStatesList->grant_access_to_first();

	while (node != nullptr)
	{
		node->data->next = matchState;
		node = node->next;
	}

	// delete outStatesList;
}

Automata::~Automata()
{
}
