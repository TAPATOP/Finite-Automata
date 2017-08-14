#include <iostream>

#include "Stack.h"
#include "StringStuff.h"

namespace ss
{
	// returns operator's precedence( e.g. order of execution compared to other operators)
	// 0 -> not an operator
	// 1 -> '*'
	// 2 -> '.'
	// 3 -> '|'
	int operator_precedence(char c)
	{
		switch (c)
		{
		case '*':
			return 1;
		case '.':
			return 2;
		case '|':
			return 3;
		}

		return 0;
	}


	// checks what type a char is:
	// / 0 -> unrecognized
	// / 1 -> operator: "*", ".", "|", "(", ")"
	// / 2 -> special symbol: "\"
	// / 3 -> operand/ base symbol: pretty much anything else
	int symbol_type(char c)
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


	// / checks validity of input
	// returns nullptr if:
	// - the given string is empty
	// - the given string has an invalid character
	// / adds explicit '.' operators
	char* preprocess_infix(char* infix)
	{
		unsigned int index = 0;
		unsigned int newSize = strlen(infix);

		// checks if string is empty //

		if (newSize == 0)
		{
			return nullptr;
		}
		///////////////////////
		// ADD EXPLICIT OPERATORS part
		//////////////////////

		// counts the number of legit characters so we know how much
		// we might have to expand the string in order to fit the new explicit '.' operators
		while (infix[index])
		{
			if (symbol_type(infix[index]) == 3)
			{
				++newSize;
			}
			index++;
		}

		// initialize the new string //

		char* newInfix = new char[newSize + 1];
		unsigned int newIndex = 0;

		newInfix[newIndex++] = infix[0];

		index = 0;

		int lastSymbolType = symbol_type(infix[index++]);
		int currentSymbolType = 0;

		// makes sure the first symbol is valid
		if (lastSymbolType == 0)
		{
			std::cout << "Unrecognized symbol!" << std::endl;
			return nullptr;
		}

		// operator adding part //

		while (infix[index])
		{
			currentSymbolType = symbol_type(infix[index]);
			
			// checks if the current symbol is valid
			if (currentSymbolType == 0)
			{
				std::cout << "Unrecognized symbol!" << std::endl;
				return nullptr;
			}

			if (infix[index - 1] == '(' && infix[index] == ')')
			{
				std::cout << "I don't understand what to do with \"()\" : (" << std::endl;
				return nullptr;
			}

			// if an operand, postfix operator(*) or closing bracket are followed by either an opening bracket
			// or another operand, then there is no operator between the two, so we need to add an explicit one
			if ((lastSymbolType == 3 || infix[index - 1] == '*' || infix[index - 1] == ')') && (infix[index] == '(' || currentSymbolType == 3))
			{
				newInfix[newIndex++] = '.';
			}

			newInfix[newIndex++] = infix[index];

			lastSymbolType = currentSymbolType;
			index++;
		}

		// terminate the new string
		newInfix[newIndex] = 0;

		return newInfix;
	}
	

	// takes an infix string, normalizes it through a helper function and
	// converts it to postfix
	// / checks validity of input
	// returns nullptr if:
	// - the brackets don't match
	char* infix_to_postfix(char* inputInfix)
	{
		char* infix = preprocess_infix(inputInfix);

		if (infix == nullptr) return nullptr;

		int infixSize = strlen(infix);

		const int maxSize = 1024;

		if (infixSize > maxSize)
		{
			std::cout << "Too large regex" << std::endl;
			return nullptr;
		}

		char* postfix = new char[maxSize + 1];

		Stack<char> stack(maxSize);

		int iIndex = 0;
		int pIndex = 0;
		char currentSymbol = 0;

		while (infix[iIndex])
		{
			currentSymbol = infix[iIndex++];
			int charType = symbol_type(currentSymbol);

			if (charType == 3)
			{
				postfix[pIndex++] = currentSymbol;
				continue;
			}


			if (currentSymbol == '(')
			{
				stack.push(currentSymbol);
				continue;
			}

			if (currentSymbol == ')')
			{
				do
				{
					if (stack.top() != '(')
					{
						postfix[pIndex++] = stack.topNpop();
					}

					if (stack.isEmpty())
					{
						std::cout << "Bracket error" << std::endl;
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

			// handle operators //
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
			if (currentSymbol == '(')
			{
				std::cout << "Bracket error" << std::endl;
				return nullptr;
			}
			
			postfix[pIndex++] = currentSymbol;
			
		}
		postfix[pIndex] = 0;
		return postfix;
	}
};