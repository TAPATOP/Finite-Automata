#include <iostream>

#include "Automata.h"
#include "LinkedList.h"
#include "Stack.h"
#include "State.h"
#include "StringStuff.h"

int main(int argc, char** argv)
{
	argv[1] = "file.txt";
	argv[2] = "\\\\\\\\\\\\";
	
	argc = 3;

	///////////////////////////////
	// REGEX PREPROCESSING 
	//////////////////////////////

	char* postfix = ss::infix_to_postfix(argv[2]);

	// checks if preprocess_infix() or infix_to_postfix() have found an error;
	// doesnt output anything because these functions already do
	if (postfix == nullptr)
	{
		return 1;
	}

	std::cout << postfix << std::endl;

	/////////////////////
	// AUTOMATA BUILDING
	/////////////////////

	int index = 0;
	int currSymbolType = 0;
	char currSymbol = 0;

	Stack<Automata*> automataStack;
	State* stateToPush = nullptr;
	Automata* automataToPush = nullptr;
	Automata* a1 = nullptr;
	Automata* a2 = nullptr;

	do
	{
		currSymbolType = ss::symbol_type(postfix[index]);
		currSymbol = postfix[index];

		switch (currSymbolType)
		{
		case 2:
		case 3:
			stateToPush = new State(get_state_transition_value_by_char(currSymbol));
			
			automataToPush = new Automata(stateToPush, new LinkedList<State*>(stateToPush));
			automataStack.push(automataToPush);
			break;
		case 1:
			switch (currSymbol)
			{
			case '.':
				a2 = automataStack.topNpop();
				if (automataStack.isEmpty())
				{
					std::cout << "Error with operator count or positioning" << std::endl;
					return 2;
				}
				a1 = automataStack.topNpop();
				a1->concatenate_with(a2);

				automataStack.push(a1);
				break;
			case '*':
				if (automataStack.isEmpty())
				{
					std::cout << "Error with operator count or positioning" << std::endl;
					return 2;
				}
				a1 = automataStack.topNpop();
				a1->iterate();

				automataStack.push(a1);
				break;
			case '|':
				a2 = automataStack.topNpop();
				if (automataStack.isEmpty())
				{
					std::cout << "Error with operator count or positioning" << std::endl;
					return 2;
				}
				a1 = automataStack.topNpop();
				a1->alternate_with(a2);

				automataStack.push(a1);
				break;
			}
			break;
		}

	} while (postfix[index++]);

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

// / preprocess_infix() testing( + testing results in infix_to_postfix())
// ab(c*d)e
// a(b*cd)|ef and a.(b*.c.d)|e.f
// ((ab|cd)*(wx|yz)) and ((a.b|c.d)*.(w.x|y.z))
// ((a.b|cd)*(w.x|y.z))
// (a.b)*|(d*e)*
//
// / escapes testing
// \\ab\\cde\\\\ and \\\\\\\\\\\\ -> whether preprocess_infix() would allocate enough memory
// ab|\\d.c
// \\ -> doesnt add anything and doesnt blow up => success
// a.d.\\s.\\\\.e.\\\\.\\d -> same as above
// ad\\s\\\\e\\\\\\d
// ab\\s\\\\*f
// (a|\\s)*|(\\\\|\\w)(\\\\\\a)
// (a|\\s)*|(\\\\|\\d)(\\\\\\a) -> tests for valid capitalization of escaped letters without messing stuff up
// \\ab\\e\\\\\\d
// \\ab\\c\\\\\\d -> returns an error, as expected
// ad\\s\\\\\\e\\\\\\d

// /LinkedList
// while(true) {multiple enqueues and dequeues}

// / Automaton build testing
// ab
// abcde
// ab*
// (ab)*
// a|b
// (a|b)*|de
// (a*|b*)|de + manual check via debugger if ending nodes( ones where next == nullptr) are in the ending list
// ((a.b*(cd)*)|de*)|(a.d)* + same as above
// (a||\\s)*|(\\\\|\\d)(\\\\\\a) -> printed error and stopped program => great
// \\\\\\\\\\\\

// / ss::decapitalize_char()
// ((a.B*(cd)*)|de*)|(a.d)*