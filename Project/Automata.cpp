#include "Automata.h"



Automata::Automata(State * startState, LinkedList<State*> outArrows)
{
	this->startState = startState;
	this->outArrows = outArrows;
}

void Automata::concatenate_to_me(Automata * followingAutomata)
{

}

Automata::~Automata()
{
}
