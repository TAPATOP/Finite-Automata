#include <iostream>

#include "Stack.h"
#include "StringStuff.h"

namespace ss
{
	// returns operator's priority
	// 0 -> not an operator
	// 1 -> '|'
	// 2 -> '.'
	// 3 -> '*'
	int operator_precedence(char c)
	{
		switch (c)
		{
		case '|':
			return 3;
		case '.':
			return 2;
		case '*':
			return 1;
		}

		return 0;
	}

	// checks what type a char is:
	// / 0 -> unrecognized
	// / 1 -> operator: "*", ".", "|", "(", ")"
	// / 2 -> special symbol: "\"
	// / 3 -> operand/ base symbol: pretty much anything else
	int char_type(char c)
	{
		if (c < 33 || c > 126)
		{
			return 0;
		}
		if (c == '|' || c == '.' || c == '*' || c == '(' || c == ')')
		{
			return 1;
		}
		if (c == '\\')
		{
			return 2;
		}

		return 3;
	}

	// char* preprocess_infix(char* infix);

	char* infix_to_postfix(char* infix)
	{
		// preprocess_infix(infix);
		int infixSize = strlen(infix);

		if (infixSize > 1024)
		{
			std::cout << "Too large regex" << std::endl;
			return nullptr;
		}

		const int maxSize = 1024;
		char* postfix = new char[maxSize + 1];

		Stack<char> stack(maxSize);

		int iIndex = 0;
		int pIndex = 0;
		char currentSymbol = 0;

		while (infix[iIndex] != '\0')
		{
			currentSymbol = infix[iIndex++];
			int charType = char_type(currentSymbol);

			if (charType == 3)
			{
				postfix[pIndex++] = currentSymbol;
				continue;
			}


			if (currentSymbol == '(')
			{
				stack.push('(');
				continue;
			}

			if (currentSymbol == ')')
			{
				do
				{
					postfix[pIndex++] = stack.topNpop();

					if (stack.isEmpty())
					{
						return nullptr;
					}
				} while (stack.top() != '(');
				stack.pop();
				continue;
			}

			if (stack.isEmpty() || stack.top() == '(')
			{
				stack.push(currentSymbol);
				continue;
			}

			switch (currentSymbol)
			{
			case '*':
			case '.':
			case '|':
				if (operator_precedence(stack.top()) <= operator_precedence(currentSymbol))
				{
					do
					{
						postfix[pIndex++] = stack.topNpop();
					} while (stack.top() != '(' && operator_precedence(currentSymbol) <= operator_precedence(stack.top()) );
					stack.push(currentSymbol);
					break;
				}
				stack.push(currentSymbol);
				break;
			}
		}

		while (!stack.isEmpty())
		{
			currentSymbol = stack.topNpop();
			if (currentSymbol != '(')
				postfix[pIndex++] = currentSymbol;
		}
		postfix[pIndex] = 0;
		return postfix;
	}
};