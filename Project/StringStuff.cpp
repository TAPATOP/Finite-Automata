/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 0
* @compiler VC
*
*/

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


		if (infix == nullptr) return nullptr;

		///////////////////////
		// ADD EXPLICIT OPERATORS part
		//////////////////////

		// counts the number of legit characters so we know how much
		// we might have to expand the string in order to fit the new explicit '.' operators
		int currentSymbolType = 0;
		bool lastSymbolWasSpecial = 0;
		while (infix[index])
		{
			// if (infix == nullptr) return nullptr; // TODO: why did i put this here??

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
						std::cout << "You can't escape operators or unknown characters" << std::endl;
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
		if (lastSymbolType == 2)
		{
			lastSymbolWasSpecial = 1;
		}
		else
		{
			lastSymbolWasSpecial = 0;
		}

		// insert the operators //
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

			// this if does the same as the one above but separating them makes the code a bit more readable?
			// if both the last and current symbols are '\\', add an operator, since we have a '\\' operand
			if (newIndex > 1 && symbol_type(newInfix[newIndex - 2]) == 2 && symbol_type(newInfix[newIndex - 1]) == 2 &&
				(infix[index] == '(' || currentSymbolType == 3 || currentSymbolType == 2))
			{
				newInfix[newIndex++] = '.';
			}
			
			newInfix[newIndex++] = infix[index];
			
			lastSymbolType = currentSymbolType;
			index++;
		}

		// terminate the new string
		newInfix[newIndex] = 0;

		newInfix = squish_infix(newInfix);

		return newInfix;
	}


	char * squish_infix(char * infix)
	{
		bool lastSymbolWasSpecial = 0;

		int squishedIndex = 0;
		int oldIndex = 0;

		// handle the first symbol //

		if (symbol_type(infix[oldIndex]) == 2)
		{
			lastSymbolWasSpecial = 1;
		}
		else
		{
			++squishedIndex;
		}
		++oldIndex;

		// iterate throghout the remaining string //

		while (infix[oldIndex])
		{
			char newChar = decapitalize_char(infix[oldIndex]);

			if (lastSymbolWasSpecial)
			{
				lastSymbolWasSpecial = 0;
				// saves the escaped symbols by capitalizing them and overwriting
				// the escaping '\\'
				if (!can_escape(newChar))
				{
					std::cout << "You cannot escape this symbol!" << std::endl;
					return nullptr;
				}
				infix[squishedIndex++] = capitalize_char(newChar);
			}
			else
			{
				infix[squishedIndex] = newChar;
				if (symbol_type(newChar) == 2)
				{
					lastSymbolWasSpecial = 1;
				}
				else
				{
					++squishedIndex;
				}
			}
			oldIndex++;
		}
		if (lastSymbolWasSpecial)
		{
			std::cout << "Please take a look at your escape sequences attempts" << std::endl;
			return nullptr;
		}
		infix[squishedIndex] = 0;
		return infix;
	}
	

	char* infix_to_postfix(char* inputInfix)
	{
		if (strlen(inputInfix) == 0)
		{
			return "E";
		}
		char* infix = preprocess_infix(inputInfix);

		// if infix == nullptr, preprocess_infix() has already printed out a message so we 
		// dont need to print anything now
		if (infix == nullptr) return nullptr;

		int infixSize = strlen(infix);

		const int MAX_SIZE = 1024;

		if (infixSize > MAX_SIZE)
		{
			std::cout << "Too large regex" << std::endl;
			return nullptr;
		}

		char* postfix = new char[infixSize + 1];

		Stack<char> stack(infixSize);

		int iIndex = 0;
		int pIndex = 0;
		char currentSymbol = 0;

		while (infix[iIndex])
		{
			currentSymbol = infix[iIndex++];
			int charType = symbol_type(currentSymbol);

			if (charType == 3 || charType == 2)
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
					} while (!stack.isEmpty() && stack.top() != '(' && operator_precedence(currentSymbol) > operator_precedence(stack.top()) );
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