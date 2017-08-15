#pragma once

#include "LinkedList.h"
#include "State.h"

class Automata
{
public:
	Automata(State* startState, LinkedList<State>* outArrowsList);

	void concatenate_to_me(Automata* followingAutomata);

	~Automata();
private:
	State* startState = nullptr;
	LinkedList<State>* outArrowsList;
};

