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

////////////////////////////////////////////////////////////////
/// \ brief
/// Presents the States of which automatas are built of
/// \ contains
/// \\ character code that can be used to pass this state and enter the next one
/// \\ two pointers to other states
/// \\ ID of the list the State belongs to( used when working with the Automata)
///
////////////////////////////////////////////////////////////////
#pragma once

#include "LinkedList.h"

enum StateTransitionCodes
{
	Digit = 127,
	Letter,
	Space,
	Empty,
	Split,
	Match
};

struct State
{
	State(int transitionCharacter, State* first = nullptr, State* second = nullptr);

	void process_symbol(char c, LinkedList<State*>* listForEnqueue, int listID);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// enqueues this to the given list and technically passes the null string to Split states
	/// to it, resulting in recursive search for states that have a stateValue != Split
	/// \ TL;DR: Add States by this function, this way you will make sure the states saved
	/// in the list are ones which recognize symbols and are not Splitting States
	///
	////////////////////////////////////////////////////////////////
	void get_enqueued(LinkedList<State*>* listForEnqueue, int listID);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// sets this state AND EVERY SINGLE STATE IT'S CONNECTED TO's listID to -1
	///
	////////////////////////////////////////////////////////////////
	void reset_states();

	void delete_states();

	~State();
private:
	////////////////////////////////////////////////////////////////
	/// returns depending on character type:
	/// 0 -> none of the below
	/// 1 -> letter
	/// 2 -> digit
	///
	////////////////////////////////////////////////////////////////
	int symbol_type(char c);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// Tells the State if it can be passed with the given char
	///
	////////////////////////////////////////////////////////////////
	bool can_match_symbol(char c);

public:
	unsigned short transitionCharacter = 0;
	State* next = nullptr;
	State* next2 = nullptr;
	int listID = -1;
};

////////////////////////////////////////////////////////////////
/// \ brief
/// Returns the value you'd need to have to pass a State with the current char
/// \ returns
/// \\ the char itself, converted to int, if it's not a special one
/// \\ the corresponding special code( usually due to the char being escaped earlier
/// in the program), described in enum StateTransitionCodes
///
////////////////////////////////////////////////////////////////
int get_state_transition_value_by_char(char c);
