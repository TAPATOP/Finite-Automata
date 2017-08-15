#pragma once

#include "LinkedList.h"
#include "State.h"

// / brief
// literally two pointers
// / not as brief
// tracks an Automata, by presenting it by it's starting state and the collection
// of ending states, similarly to the ways lists are tracked
class Automata
{
public:
	Automata();
	Automata(State* startState, LinkedList<State*>* outArrowsList);

	void concatenate_with(Automata* followingAutomata);

	~Automata();
private:
	State* startState;
	LinkedList<State*>* outArrowsList;
};

