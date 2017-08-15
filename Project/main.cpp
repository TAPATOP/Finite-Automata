#include <iostream>

#include "Automata.h"
#include "LinkedList.h"
#include "Stack.h"
#include "State.h"
#include "StringStuff.h"

int main(int argc, char** argv)
{
	argv[1] = "file.txt";
	argv[2] = "abcde";
	argc = 3;

	char* postfix = ss::infix_to_postfix(argv[2]);

	// checks if preprocess_infix() or infix_to_postfix() have found an error;
	// doesnt output anything because these functions already do
	if (postfix == nullptr)
	{
		return 1;
	}

	std::cout << postfix << std::endl;

	int index = 0;
	int currSymbolType = 0;
	char currSymbol = 0;

	Stack<Automata*> automataStack;
	State* stateToPush = nullptr;
	Automata* automataToPush = nullptr;
	do
	{
		currSymbolType = ss::symbol_type(postfix[index]);
		currSymbol = postfix[index];

		switch (currSymbolType)
		{
		case 3:
			stateToPush = new State(currSymbol);
			
			automataToPush = new Automata(stateToPush, new LinkedList<State*>(stateToPush));
			automataStack.push(automataToPush);
			break;
		case 1:
			switch (currSymbol)
			{
			case '.':
				Automata* a2 = automataStack.topNpop();
				Automata* a1 = automataStack.topNpop();

				a1->concatenate_with(a2);

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

// / preprocess_infix() testing + testing results in infix_to_postfix()
// ab(c*d)e
// a(b*cd)|ef and a.(b*.c.d)|e.f
// ((ab|cd)*(wx|yz)) and ((a.b|c.d)*.(w.x|y.z))
// ((a.b|cd)*(w.x|y.z))