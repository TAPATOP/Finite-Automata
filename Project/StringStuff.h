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

#pragma once

namespace ss
{
	////////////////////////////////////////////////////////////////
	/// \ brief 
	/// returns operator's precedence( e.g. order of execution compared to other operators)
	/// 0 -> not an operator
	/// 1 -> '*'
	/// 2 -> '.'
	/// 3 -> '|'
	///
	////////////////////////////////////////////////////////////////
	int operator_precedence(char c);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// \ returns; checks what type a char is
	/// \ 0 -> unrecognized
	/// \ 1 -> operator: "*", ".", "|", "(", ")"
	/// \ 2 -> special symbol: "\"
	/// \ 3 -> operand/ base symbol: pretty much anything else
	///
	////////////////////////////////////////////////////////////////
	int symbol_type(char c);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// tells whether the given character has an escape sequence assosiated with it
	/// returns true for: 'e', 'a', 'd', 's' and '\\'
	///
	////////////////////////////////////////////////////////////////
	bool can_escape(char c);

	////////////////////////////////////////////////////////////////
	/// \ brief 
	/// \ checks validity of input
	/// returns nullptr if:
	/// \\ the given string is empty
	/// \\ the given string has an invalid character
	/// \ adds explicit '.' operators
	/// \ returns a dynamycally allocated char array
	///
	////////////////////////////////////////////////////////////////
	char* preprocess_infix(char* infix);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// squishes '\\' and the escaped character into one so they can be pushed
	/// down the stack as a single char
	/// \ checks validity of input 
	/// returns nullptr if:
	/// \\ the given string had an escape character infront of something you can't escape
	/// \ inplace work
	/// changes the given character itself, so you really shouldn't try giving a const string
	///
	////////////////////////////////////////////////////////////////
	char* squish_infix(char* infix);

	////////////////////////////////////////////////////////////////
	/// \brief
	/// takes an infix string, normalizes it through a helper function and
	/// converts it to postfix
	/// \ checks validity of input
	/// returns nullptr if:
	/// \\ the brackets don't match
	///
	////////////////////////////////////////////////////////////////
	char* infix_to_postfix(char* infix);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// decapitalizes the given symbol if it's a captal letter
	/// \ returns
	/// \\ the decapitalized symbol, if that makes sense for the 
	/// given one
	///
	////////////////////////////////////////////////////////////////
	char decapitalize_char(char symbol);

	////////////////////////////////////////////////////////////////
	/// \ brief
	/// decapitalizes the given letter;
	/// \ returns 
	/// \\ the capitalized symbol; or:
	/// \\ the symbol itself if it cannot be decapitalized
	///
	////////////////////////////////////////////////////////////////
	char capitalize_char(char symbol);
};