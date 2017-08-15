#pragma once

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

	unsigned short transitionCharacter = 0;
	State* next = nullptr;
	State* next2 = nullptr;
	int listID = -1;

	~State();
};