#include "Automata.h"



Automata::Automata(State * startState, LinkedList<State>* outArrowsList)
{
	this->startState = startState;
	this->outArrowsList = outArrowsList;
}

void Automata::concatenate_to_me(Automata * followingAutomata)
{
	this->outArrowsList->concatenate_to_me(followingAutomata->outArrowsList);
}

Automata::~Automata()
{
}
