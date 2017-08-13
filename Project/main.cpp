#include <iostream>

#include "Stack.h"
#include "StringStuff.h"

char* re2post(char *re)
{
	int nalt, natom;
	static char buf[8000];
	char *dst;

	struct 
	{
		int nalt;
		int natom;
	} paren[100], *p;

	p = paren;
	dst = buf;
	nalt = 0;
	natom = 0;
	if (strlen(re) >= sizeof buf / 2)
		return NULL;
	for (; *re; re++) {
		switch (*re) {
		case '(':
			if (natom > 1) {
				--natom;
				*dst++ = '.';
			}
			if (p >= paren + 100)
				return NULL;
			p->nalt = nalt;
			p->natom = natom;
			p++;
			nalt = 0;
			natom = 0;
			break;
		case '|':
			if (natom == 0)
				return NULL;
			while (--natom > 0)
				*dst++ = '.';
			nalt++;
			break;
		case ')':
			if (p == paren)
				return NULL;
			if (natom == 0)
				return NULL;
			while (--natom > 0)
				*dst++ = '.';
			for (; nalt > 0; nalt--)
				*dst++ = '|';
			--p;
			nalt = p->nalt;
			natom = p->natom;
			natom++;
			break;
		case '*':
		case '+':
		case '?':
			if (natom == 0)
				return NULL;
			*dst++ = *re;
			break;
		default:
			if (natom > 1) {
				--natom;
				*dst++ = '.';
			}
			*dst++ = *re;
			natom++;
			break;
		}
	}
	if (p != paren)
		return NULL;
	while (--natom > 0)
		*dst++ = '.';
	for (; nalt > 0; nalt--)
		*dst++ = '|';
	*dst = 0;
	return buf;
}

int main()
{
	char* test = "((a.b|c.d)*.(w.x|y.z))";
	std::cout << ss::infix_to_postfix(test) << std::endl;
	//std::cout << re2post("((ab|cd)*(wx|yz))") << std::endl;
	//std::cout << re2post("((ab*(cd)*)|de*)|(ad)*") << std::endl;
	// ((a.b*.(c.d)*)|d.e*)|(a.d)*
	return 0;
}