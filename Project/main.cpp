#include <iostream>
#include <fstream>

#include "Automata.h"
#include "LinkedList.h"
#include "Stack.h"
#include "State.h"
#include "StringStuff.h"

int main(int argc, char** argv)
{
	argv[1] = "file.txt";
	argv[2] = "\\ead\\e";
	
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
	int stateTransitionValue = 0;

	Stack<Automata*> automataStack;
	State* stateToPush = nullptr;

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
			stateTransitionValue = get_state_transition_value_by_char(currSymbol);
			if (stateTransitionValue == StateTransitionCodes::Empty)
			{
				stateToPush = new State(StateTransitionCodes::Split);
				stateToPush->next2 = stateToPush;
			}
			else
			{
				stateToPush = new State(stateTransitionValue);
			}
			
			a1 = new Automata(stateToPush, new LinkedList<State*>(stateToPush));
			automataStack.push(a1);
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

	// finalization of automata and error check //

	Automata* readyAutomata = automataStack.topNpop();

	if (!automataStack.isEmpty())
	{
		std::cout << "I believe you have missing operators" << std::endl;
		return 3;
	}

	if (!readyAutomata->finalize())
	{
		return 4;
	}

	////////////////////////
	// READ AND MATCH DATA
	//////////////////////

	readyAutomata->prepare_for_reading();

	std::ifstream inputFile(argv[1]);

	const int MAX_TEXT_SIZE = 1024;
	char* inputText = new char[MAX_TEXT_SIZE + 1];

	index = 0;
	int lineCounter = 1;
	while (!inputFile.eof())
	{
		inputFile.getline(inputText, MAX_TEXT_SIZE);
		inputText[inputFile.gcount()] = 0;

		while (inputText[index])
		{

			index++;
		}
	}
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
// (a\\\\)|a*.d
// a|a*.b
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
// \\a\\\\\\\\\\\\\\d\\d\\ -> returns an error for having a lonely (._. ) escape character

// /LinkedList
// while(true) {multiple enqueues and dequeues}

// / Automata build testing
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
// \\e
// ((a.b)*|de)|\\ea
// \\e\\d\\a|\\s\\\\

// / ss::decapitalize_char()
// ((a.B*(cd)*)|de*)|(a.d)*