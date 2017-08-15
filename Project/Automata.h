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
	Automata(State* startState, LinkedList<State*>* outStatesList);


	// makes all the outStates of the current Automata point towards
	// the beginning of the followingAutomata and makes the followingAutomata's
	// outStatesList the new outArrowList of the current Automata by copying it's address
	// !!! WARNING !!!
	// Destroys the followingAutomata because you should not be able to access it directly after
	// the concatenation has taken place( since, technically, you have >merged< two Automatas into one
	void concatenate_with(Automata* followingAutomata);

	// creates a new SPLIT state, connects it with the startingState of the Automata,
	// connects the ending states with it and adds it to outStatesList
	void iterate();

	void alternate_with(Automata* alternateAutomata);

	//void destroy_machine();

	~Automata();
private:
	State* startState;
	LinkedList<State*>* outStatesList;
};

