#pragma once

namespace ss
{
	// returns operator's precedence( e.g. order of execution compared to other operators)
	// 0 -> not an operator
	// 1 -> '*'
	// 2 -> '.'
	// 3 -> '|'
	int operator_precedence(char c);


	// checks what type a char is:
	// / 0 -> unrecognized
	// / 1 -> operator: "*", ".", "|", "(", ")"
	// / 2 -> special symbol: "\"
	// / 3 -> operand/ base symbol: pretty much anything else
	int symbol_type(char c);


	// / checks validity of input
	// returns nullptr if:
	// - the given string is empty
	// - the given string has an invalid character
	// / adds explicit '.' operators
	// / returns a dynamycally allocated char array
	char* preprocess_infix(char* infix);


	// takes an infix string, normalizes it through a helper function and
	// converts it to postfix
	// / checks validity of input
	// returns nullptr if:
	// - the brackets don't match
	char* infix_to_postfix(char* infix);
};