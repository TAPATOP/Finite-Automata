#include "Automata.h"



Automata::Automata()
{
	startState = nullptr;
	outArrowsList = nullptr;
}

Automata::Automata(State* startState, LinkedList<State*>* outArrowsList)
{
	this->startState = startState;
	this->outArrowsList = outArrowsList;
}

void Automata::concatenate_with(Automata* followingAutomata)
{
	this->outArrowsList->concatenate_with(followingAutomata->outArrowsList);
}

Automata::~Automata()
{
}
