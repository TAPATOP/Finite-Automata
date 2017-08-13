#pragma once

namespace ss
{
	int operator_precedence(char c);
	int symbol_type(char c);
	char* preprocess_infix(char* infix);
	char* infix_to_postfix(char* infix);
};