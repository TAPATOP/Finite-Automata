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

#pragma once

#include "LinkedList.h"
#include "State.h"
/////////////////////////////////////////////
/// / brief
/// literally two pointers
/// / not as brief
/// tracks an Automata, by presenting it by it's starting state and the collection
/// of ending( and later on- active) states, similarly to the ways lists are tracked
///
//////////////////////////////////////////////
class Automata
{
public:
	Automata();
	Automata(State* startState, LinkedList<State*>* outStatesList);

	////////////////////////////////////////////////////////////////////////
	/// \ brief
	/// makes all the outStates of the current Automata point towards
	/// the beginning of the followingAutomata and makes the followingAutomata's
	/// outStatesList the new outArrowList of the current Automata by copying it's address
	/// !!! WARNING !!!
	/// Destroys the followingAutomata because you should not be able to access it directly after
	/// the concatenation has taken place( since, technically, you have >merged< two Automatas into one
	///
	/////////////////////////////////////////////////////////////////////////
	void concatenate_with(Automata* followingAutomata);

	/////////////////////////////////////////////////////////////////////////
	/// creates a new SPLIT state, connects it with the startingState of the Automata,
	/// connects the ending states with it and adds it to outStatesList
	///
	/////////////////////////////////////////////////////////////////////////
	void iterate();

	/////////////////////////////////////////////////////////////////////////
	/// \ brief
	/// creates a new SPLIT state, makes it the startingState of the Automata, 
	/// connects the endingStates lists of the two automatas
	/// !!! WARNING !!!
	/// Destroys the alternateAutomata because you should not be able to access it directly after
	/// the alternation has taken place( since, technically, you have >merged< two Automatas into one
	///
	/////////////////////////////////////////////////////////////////////////
	void alternate_with(Automata* alternateAutomata);

	/////////////////////////////////////////////////////////////////////////
	/// \ brief
	/// adds a final state and connects all nodes to it, emptying outStatesList in the process
	/// \ return whether finalization is successful
	///
	/////////////////////////////////////////////////////////////////////////
	bool finalize();

	/////////////////////////////////////////////////////////////////////////
	/// \ brief
	/// adds the startStart into the outStatesList; it's gonna be used when reading characters
	/// so I don't have to allocate a new list
	///
	/////////////////////////////////////////////////////////////////////////
	void prepare_for_reading();

	/////////////////////////////////////////////////////////////////////////
	/// \brief
	/// traverses the automata based on the given character; gives the letter
	/// too all the active states that are queued in the list
	/// \return:
	/// \\ 1 if no states match the letter
	/// \\ 0 if success
	///
	/////////////////////////////////////////////////////////////////////////
	int process_letter(char c, int listID);


	/////////////////////////////////////////////////////////////////////////
	/// \brief 
	/// traverses the outStatesList and checks if any of the States in it is Match
	/// ! WARNING !
	/// dequeues all of the States, thus preparing the Automata to work again
	/// \ return
	/// \\ true if the automata has matched the input
	/// \\ false if not
	///
	/////////////////////////////////////////////////////////////////////////
	bool dump_all_and_match();

	void destroy_machine(); // this is needed because we don't want the destructor to destroy everything

	~Automata();
private:
	/////////////////////////////////////////////////////////////////////////
	/// \ brief
	/// sets all States' listID to -1
	///
	/////////////////////////////////////////////////////////////////////////
	void reset_states();
private:
	State* startState;
	LinkedList<State*>* outStatesList;
};

// TODO: stop deleting shit here
