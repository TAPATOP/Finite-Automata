#include <iostream>

#include "LinkedList.h"
#include "Stack.h"
#include "StringStuff.h"

struct State
{
	unsigned short transitionCharacter = 0;
	State* next = nullptr;
	State* next2 = nullptr;
	int listID = 0;
};

int main()
{
	std::cout << (unsigned short)-1 << std::endl;
	char* test = "((a.b|cd)*(w.x|y.z))";
	char* test2 = "((ab|cd)*(wx|yz))";
	char* testTransformed = ss::preprocess_infix(test);

	//if (testTransformed != nullptr)
	{
		std::cout << testTransformed << std::endl;
	}
	std::cout << ss::infix_to_postfix(testTransformed) << std::endl;
	std::cout << ss::infix_to_postfix(test2) << std::endl;
	return 0;
}

// TODO: Big three for the structures

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