#include <iostream>

#include "Stack.h"
#include "StringStuff.h"

namespace ss
{
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


	bool can_escape(char c)
	{
		switch (c)
		{
		case 'a':
		case 'e':
		case 's':
		case 'd':
		case '\\':
			return 1;
			break;
		}
		return 0;
	}


	char* preprocess_infix(char* infix)
	{
		unsigned int index = 0;
		unsigned int newSize = strlen(infix);

		// checks if string is empty //

		if (newSize == 0)
		{
			return nullptr; // should be made a bit different
		}
		///////////////////////
		// ADD EXPLICIT OPERATORS part
		//////////////////////

		// counts the number of legit characters so we know how much
		// we might have to expand the string in order to fit the new explicit '.' operators
		int currentSymbolType = 0;
		bool lastSymbolWasSpecial = 0;
		while (infix[index])
		{
			if (infix == nullptr) return nullptr;

			currentSymbolType = symbol_type(infix[index]);
			if (currentSymbolType == 3)
			{
				++newSize;
				lastSymbolWasSpecial = 0;
			}
			else
			{
				if (currentSymbolType == 2)
				{
					// if both the last and current symbols were '\\' then we have a
					// '\\' in the role of an operand
					if (lastSymbolWasSpecial == 1)
					{
						lastSymbolWasSpecial = 0;
						++newSize;
					}
					else
					{
						lastSymbolWasSpecial = 1;
					}
				}
				else
				{
					// if you get to this points it means the symbol is either an operator or unknown
					if (lastSymbolWasSpecial)
					{
						std::cout << "You can't escape this character !!11" << std::endl;
						return nullptr;
					}
					lastSymbolWasSpecial = 0;
				}
			}

			index++;
		}

		// initialize the new string //

		char* newInfix = new char[newSize + 1];
		unsigned int newIndex = 0;

		newInfix[newIndex++] = decapitalize_char(infix[0]);

		index = 0;

		int lastSymbolType = symbol_type(infix[index++]);
		currentSymbolType = 0;

		// makes sure the first symbol is valid
		if (lastSymbolType == 0)
		{
			std::cout << "Unrecognized symbol!" << std::endl;
			return nullptr;
		}

		// operator adding part //

		lastSymbolWasSpecial = 0;

		while (infix[index])
		{
			currentSymbolType = symbol_type(infix[index]);
			
			// checks if the current symbol is valid
			if (currentSymbolType == 0)
			{
				std::cout << "Unrecognized symbol!" << std::endl;
				return nullptr;
			}

			// checks for a specific case
			if (infix[index - 1] == '(' && infix[index] == ')')
			{
				std::cout << "I don't understand what to do with \"()\" : (" << std::endl;
				return nullptr;
			}

			// if an operand, postfix(unary) operator(*) or closing bracket are followed by either an opening bracket
			// or another operand, then there is no operator between the two, so we need to add an explicit one
			if ((lastSymbolType == 3 || infix[index - 1] == '*' || infix[index - 1] == ')') && // last symbol
				(infix[index] == '(' || currentSymbolType == 3 || currentSymbolType == 2)) // current symbol
			{
				newInfix[newIndex++] = '.';
			}

			// this does the same but separating them makes the code a bit more readable?
			// if both the last and current symbols are '\\', add an operator, since we have a '\\' operand
			if (index > 1 && symbol_type(newInfix[newIndex - 2]) == 2 && symbol_type(newInfix[newIndex - 1]) == 2 &&
				(infix[index] == '(' || currentSymbolType == 3 || currentSymbolType == 2))
			{
				newInfix[newIndex++] = '.';
			}
			char newChar = decapitalize_char(infix[index]);

			if (!lastSymbolWasSpecial)
			{
				newInfix[newIndex++] = newChar;
				if (symbol_type(newChar) == 2)
				{
					lastSymbolWasSpecial = 1;
				}
			}
			else
			{
				if (!can_escape(newChar))
				{
					std::cout << "You cannot escape this symbol!" << std::endl;
					return nullptr;
				}

				lastSymbolWasSpecial = 0;
				if (symbol_type(newInfix[newIndex - 1]) != 2)
				{
					newIndex++;
				}
				newInfix[newIndex - 1] = capitalize_char(newChar);
			}
			
			lastSymbolType = currentSymbolType;
			index++;
		}

		// terminate the new string
		newInfix[newIndex] = 0;

		return newInfix;
	}
	

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
	
	
	char decapitalize_char(char symbol)

	{
		if (symbol >= 'A' && symbol <= 'Z')
		{
			return symbol + ('a' - 'A');
		}
		return symbol;
	}

	char capitalize_char(char symbol)
	{
		if (symbol >= 'a' && symbol <= 'z')
		{
			return symbol - ('a' - 'A');
		}
		return symbol;
	}
};