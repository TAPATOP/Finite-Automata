#pragma once

namespace ss
{
	int operator_precedence(char c);
	int char_type(char c);
	char* infix_to_postfix(char* infix);
};