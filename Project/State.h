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

	bool can_match_symbol(char c, LinkedList<State*>* stateList, int listID);
	void get_enqueued(LinkedList<State*>* stateList, int listID);

	~State();
// i know this "public" is ambigious but it makes reading the struct easier
public:
	unsigned short transitionCharacter = 0;
	State* next = nullptr;
	State* next2 = nullptr;
	int listID = -1;
private:
	int symbol_type(char c);
};

int get_state_transition_value_by_char(char c);
