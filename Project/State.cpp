#include "State.h"



State::State(int transitionCharacter, State* first, State* second)
{
	this->transitionCharacter = transitionCharacter;
	this->next = first;
	this->next2 = second;
}


State::~State()
{
}

int get_state_transition_value_by_char(char c)
{
	switch (c)
	{
	case 'A':
		return StateTransitionCodes::Letter;
	case 'D':
		return StateTransitionCodes::Digit;
	case 'S':
		return StateTransitionCodes::Space;
	case 'E':
		return StateTransitionCodes::Empty;
	default:
		return c;
	}
}
