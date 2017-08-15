#include <iostream>

#include "Automata.h"
#include "LinkedList.h"
#include "Stack.h"
#include "State.h"
#include "StringStuff.h"

int main(int argc, char** argv)
{
	State* a = new State('a');
	LinkedList<State*>* list = new LinkedList<State*> (a->next);
	Automata* alpha = new Automata(a, list);

	Stack<int> beta(5);
	beta.push(8);
	beta.push(69);

	Stack<int> gamma = beta;

	beta.push(1488);

	gamma.visualize();

	argv[1] = "file.txt";
	argv[2] = "((a|b)|(c|d))|(e|f)";
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

	Stack<Automata> autoStack;
	
	do
	{
		currSymbolType = ss::symbol_type(postfix[index]);
		currSymbol = postfix[index];

		switch (currSymbolType)
		{
		case 3:
			State* stateToPush = new State(currSymbol);
			//Automata* automataToPush = new Automata(stateToPush, )
			//autoStack.push();
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