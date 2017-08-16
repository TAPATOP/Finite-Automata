/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 0
* @compiler VC
*
*/

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

bool Automata::finalize()
{
	// create the matching state
	State* matchState = new State(StateTransitionCodes::Match);

	State* state = nullptr;

	if (outStatesList == nullptr)
	{
		std::cout << "The Automata hasn't even been initialized?" << std::endl;
		return 0;
	}

	// connect all outArrows to the matching state
	while (!outStatesList->is_empty())
	{
		state = outStatesList->dequeue();
		state->next = matchState;
	}
	return 1;
}

void Automata::prepare_for_reading()
{
	reset_states();
	startState->get_enqueued(outStatesList, 0);
}

int Automata::process_letter(char c, int listID)
{
	LinkedList<State*>* newList = new LinkedList<State*>;

	State* state = nullptr;

	while (!outStatesList->is_empty())
	{
		state = outStatesList->dequeue();

		state->process_symbol(c, newList, listID);
	}

	// returns error if the list is empty, which means no states have managed to
	// execute the current letter which means the automata is bork

	delete outStatesList;

	outStatesList = newList; 
	
	if (newList->is_empty())  return 1;

	return 0;
}

bool Automata::dump_all_and_match()
{
	bool hasMatched = 0;
	while (!outStatesList->is_empty())
	{
		if (outStatesList->dequeue()->transitionCharacter == StateTransitionCodes::Match)
		{
			hasMatched = 1;
		}
	}

	return hasMatched;
}

void Automata::destroy_machine()
{
	startState->delete_states();
}

Automata::~Automata()
{
}

void Automata::reset_states()
{
	startState->reset_states();
}
