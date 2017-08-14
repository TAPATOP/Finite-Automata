#include <iostream>

#include "Automata.h"
#include "LinkedList.h"
#include "Stack.h"
#include "State.h"
#include "StringStuff.h"

int main(int argc, char** argv)
{
	LinkedList<int> a;

	int test1 = 1;
	int test2 = 2;
	int test3 = 3;
	a.enqueue(&test1);
	a.enqueue(&test2);
	a.enqueue(&test3);

	LinkedList<int>* b = new LinkedList<int>;

	b->enqueue(&test1);
	b->enqueue(&test2);
	b->enqueue(&test3);

	a.concatenate_to_me(b);

	if(!a.is_empty()) std::cout << *(a.dequeue()) << std::endl;
	if (!a.is_empty()) std::cout << *(a.dequeue()) << std::endl;
	if (!a.is_empty()) std::cout << *(a.dequeue()) << std::endl;
	if (!a.is_empty()) std::cout << *(a.dequeue()) << std::endl;



	//Automata alpha;

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

	int index = 0;
	//Stack<
	do
	{
		// if()
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