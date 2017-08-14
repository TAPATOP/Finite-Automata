#include <iostream>

#include "LinkedList.h"
#include "Stack.h"
#include "StringStuff.h"
enum StateTransitionCodes
{
	Split = 127,
	Match,
	Digit,
	Letter
};

struct State
{
	unsigned short transitionCharacter = 0;
	State* next = nullptr;
	State* next2 = nullptr;
	int listID = -1;
};

struct Automata
{
	State* startState = nullptr;
	LinkedList<State*> endStates;
};

int main(int argc, char** argv)
{
	argv[1] = "file.txt";
	argv[2] = "?{!";
	argc = 3;

	char* postfix = ss::infix_to_postfix(argv[2]);

	// checks if preprocess_infix() or infix_to_postfix() have found an error;
	// doesnt output anything because these functions already do
	if (postfix == nullptr)
	{
		return 1;
	}

	std::cout << postfix << std::endl;

	return 0;
}

// TODO: Big three for the structures
// make it work with empty regex

// / infix_to_postfix() testing with valid expressions
// a.(b*.c.d)|e.f
// ((a.b|c.d)*.(w.x|y.z))
// a.b.((((c.d).m).n))
// ((a.b*.(c.d)*)|d.e*)|(a.d)*
// (a.b)|(c.d)|(x.y) and a.b|c.d|x.y

// / preprocess_infix() testing + testing results in infix_to_postfix()
// ab(c*d)e
// a(b*cd)|ef and a.(b*.c.d)|e.f
// ((ab|cd)*(wx|yz)) and ((a.b|c.d)*.(w.x|y.z))
// ((a.b|cd)*(w.x|y.z))