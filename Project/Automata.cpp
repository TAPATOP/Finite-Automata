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

void Automata::iterate()
{
	State* newState = new State(StateTransitionCodes::Split, nullptr, this->startState);

	State* state = nullptr;

	while (!outStatesList->is_empty())
	{
		state = outStatesList->dequeue();
		state->next = newState;
	}

	startState = newState;
	outStatesList->enqueue(newState);
}

void Automata::alternate_with(Automata* alternateAutomata)
{
	State* newState = new State(StateTransitionCodes::Split, this->startState, alternateAutomata->startState);
	startState = newState;
	this->outStatesList->concatenate_with(alternateAutomata->outStatesList);
	delete alternateAutomata;
}

Automata::~Automata()
{
}
