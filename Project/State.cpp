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
