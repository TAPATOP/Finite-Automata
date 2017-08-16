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
#include <fstream>

#include "dirent.h"

#include "Automata.h"
#include "LinkedList.h"
#include "Stack.h"
#include "State.h"
#include "StringStuff.h"

// BEWARE THE FUNCTION BELOW IS STOLEN
// BEWARE THE FUNCTION BELOW IS STOLEN
// BEWARE THE FUNCTION BELOW IS STOLEN

// SOURCE OF THE STOLEN FUNCTION WHICH IS BELOW:
// https://github.com/tronkko/dirent/blob/master/examples/find.c

/* Find files and subdirectories recursively */
static int find_directory(const char *dirname, std::ofstream& output)
{
	DIR *dir;
	char buffer[PATH_MAX + 2];
	char *p = buffer;
	const char *src;
	char *end = &buffer[PATH_MAX];
	int ok;

	/* Copy directory name to buffer */
	src = dirname;
	while (p < end  &&  *src != '\0') {
		*p++ = *src++;
	}
	*p = '\0';

	/* Open directory stream */
	dir = opendir(dirname);
	if (dir != NULL) {
		struct dirent *ent;

		/* Print all files and directories within the directory */
		while ((ent = readdir(dir)) != NULL) {
			char *q = p;
			char c;

			/* Get final character of directory name */
			if (buffer < q) {
				c = q[-1];
			}
			else {
				c = ':';
			}

			/* Append directory separator if not already there */
			if (c != ':'  &&  c != '/'  &&  c != '\\') {
				*q++ = '/';
			}

			/* Append file name */
			src = ent->d_name;
			while (q < end  &&  *src != '\0') {
				*q++ = *src++;
			}
			*q = '\0';

			/* Decide what to do with the directory entry */
			switch (ent->d_type) {
			case DT_LNK:
			case DT_REG:
				/* Output file name with directory */
				output.write(buffer, strlen(buffer));
				output.write("\n", 1);
				break;

			case DT_DIR:
				/* Scan sub-directory recursively */
				if (strcmp(ent->d_name, ".") != 0
					&& strcmp(ent->d_name, "..") != 0) {
					find_directory(buffer, output);
				}
				break;

			default:
				/* Ignore device entries */
				/*NOP*/;
			}

		}

		closedir(dir);
		ok = 1;

	}
	else {
		/* Could not open directory */
		printf("Cannot open directory %s\n", dirname);
		ok = 0;
	}

	return ok;

}
// SOURCE OF THE STOLEN FUNCTION WHICH IS ABOVE:
// https://github.com/tronkko/dirent/blob/master/examples/find.c

// BEWARE THE FUNCTION ABOVE IS STOLEN
// BEWARE THE FUNCTION ABOVE IS STOLEN
// BEWARE THE FUNCTION ABOVE IS STOLEN


int main(int argc, char** argv)
{
	argv[1] = "MuhFolder";
	argv[2] = "\\ea*a*bdefop|\\e|w|w*|\\e**\\e";
	
	argc = 3;

	if (argc != 2 && argc != 3)
	{
		std::cout << "Give me ONE file/folder name, please. You can give a regex as well if you want" << std::endl;
		return -3;
	}

	if (argc == 2)
	{
		argv[2] = "";
	}

	///////////////////////////////
	// REGEX PREPROCESSING 
	//////////////////////////////

	char* postfix = ss::infix_to_postfix(argv[2]);

	// checks if preprocess_infix() or infix_to_postfix() have found an error;
	// doesnt output anything because these functions already do
	if (postfix == nullptr)
	{
		return 1;
	}

	/////////////////////
	// AUTOMATA BUILDING
	/////////////////////

	int index = 0;
	int currSymbolType = 0;
	char currSymbol = 0;
	int stateTransitionValue = 0;

	Stack<Automata*> automataStack;
	State* stateToPush = nullptr;

	Automata* a1 = nullptr;
	Automata* a2 = nullptr;

	do
	{
		currSymbolType = ss::symbol_type(postfix[index]);
		currSymbol = postfix[index];

		switch (currSymbolType)
		{
		case 2:
		case 3:
			stateTransitionValue = get_state_transition_value_by_char(currSymbol);
			if (stateTransitionValue == StateTransitionCodes::Empty)
			{
				stateToPush = new State(StateTransitionCodes::Split);
				stateToPush->next2 = stateToPush;
			}
			else
			{
				stateToPush = new State(stateTransitionValue);
			}
			
			a1 = new Automata(stateToPush, new LinkedList<State*>(stateToPush));
			automataStack.push(a1);
			break;
		case 1:
			switch (currSymbol)
			{
			case '.':
				a2 = automataStack.topNpop();
				if (automataStack.isEmpty())
				{
					std::cout << "Error with operator count or positioning" << std::endl;
					return 2;
				}
				a1 = automataStack.topNpop();
				a1->concatenate_with(a2);

				automataStack.push(a1);
				break;
			case '*':
				if (automataStack.isEmpty())
				{
					std::cout << "Error with operator count or positioning" << std::endl;
					return 2;
				}
				a1 = automataStack.topNpop();
				a1->iterate();

				automataStack.push(a1);
				break;
			case '|':
				a2 = automataStack.topNpop();
				if (automataStack.isEmpty())
				{
					std::cout << "Error with operator count or positioning" << std::endl;
					return 2;
				}
				a1 = automataStack.topNpop();
				a1->alternate_with(a2);

				automataStack.push(a1);
				break;
			}
			break;
		}

	} while (postfix[index++]);

	// finalization of automata and error check //

	Automata* readyAutomata = automataStack.topNpop();

	if (!automataStack.isEmpty())
	{
		std::cout << "I believe you have missing operators" << std::endl;
		return 3;
	}

	if (!readyAutomata->finalize())
	{
		return 4;
	}

	////////////////////////
	// READ AND MATCH DATA
	//////////////////////


	// write names of files for checking into a file //

	char* FILE_NAME_FILE = "filenames.txt";

	std::ofstream fileNames(FILE_NAME_FILE);

	if (!fileNames.is_open())
	{
		std::cout << "I can't create a new file in which to save the file names : (" << std::endl;
		return -1;
	}


	std::ifstream inputFile(argv[1]);

	if (!inputFile.is_open())
	{
		if (!find_directory(argv[1], fileNames))
		{
			std::cout << "There is neither a folder nor a file with the given name" << std::endl;
			return -2;
		}
	}
	else
	{
		fileNames.write(argv[1], strlen(argv[1]));
	}

	inputFile.close();
	fileNames.close();

	inputFile.open(FILE_NAME_FILE);

	const int MAX_TEXT_SIZE = 1024;
	char inputText [MAX_TEXT_SIZE + 1];

	index = 0;
	int lineCounter = 1;

	std::ifstream currentFile;
	
	char currentFileName[MAX_TEXT_SIZE + 1];

	// check all of the files, one by one //

	while (!inputFile.eof())
	{
		inputFile.getline(currentFileName, MAX_TEXT_SIZE);
		// currentFileName[strlen(currentFileName)] = 0;
		currentFile.open(currentFileName);

		if (!currentFile.is_open() && !inputFile.eof())
		{
			if (strcmp(currentFileName, "\n") == 0)
			{
				std::cout << strcmp(currentFileName, "\n") << std::endl;
			}
			continue;
		}

		lineCounter = 1;
		while (!currentFile.eof())
		{
			index = 0;
			currentFile.getline(inputText, MAX_TEXT_SIZE);
			// inputText[currentFile.gcount()] = 0;
			readyAutomata->prepare_for_reading();

			while (inputText[index])
			{
				if (readyAutomata->process_letter(ss::decapitalize_char(inputText[index]), index + 1) == 1) break;
				index++;
			}

			if (readyAutomata->dump_all_and_match())
			{
				std::cout << currentFileName << ":" << lineCounter << ":" << inputText << std::endl;
			}
			++lineCounter;
		}
		currentFile.close();
	}

	return 0;
}

// TODO: Big three for the structures
// fix the char*s that are allocated in postfix works - dynamic or static
// use an array queue instead of a list for the automata's work

//////////////////////////////////////////////////////////////////////////////////
///////////////// Some of the performed test examples/////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// / infix_to_postfix() testing with valid expressions
// a.(b*.c.d)|e.f
// ((a.b|c.d)*.(w.x|y.z))
// a.b.((((c.d).m).n))
// ((a.b*.(c.d)*)|d.e*)|(a.d)*
// (a.b)|(c.d)|(x.y) and a.b|c.d|x.y

// / preprocess_infix() testing( + testing results in infix_to_postfix())
// ab(c*d)e
// a(b*cd)|ef and a.(b*.c.d)|e.f
// ((ab|cd)*(wx|yz)) and ((a.b|c.d)*.(w.x|y.z))
// ((a.b|cd)*(w.x|y.z))
// (a.b)*|(d*e)*
// (a\\\\)|a*.d
// a|a*.b
//
// / escapes testing
// \\ab\\cde\\\\ and \\\\\\\\\\\\ -> whether preprocess_infix() would allocate enough memory
// ab|\\d.c
// \\ -> doesnt add anything and doesnt blow up => success
// a.d.\\s.\\\\.e.\\\\.\\d -> same as above
// ad\\s\\\\e\\\\\\d
// ab\\s\\\\*f
// (a|\\s)*|(\\\\|\\w)(\\\\\\a)
// (a|\\s)*|(\\\\|\\d)(\\\\\\a) -> tests for valid capitalization of escaped letters without messing stuff up
// \\ab\\e\\\\\\d
// \\ab\\c\\\\\\d -> returns an error, as expected
// ad\\s\\\\\\e\\\\\\d
// \\a\\\\\\\\\\\\\\d\\d\\ -> returns an error for having a lonely (._. ) escape character

// /LinkedList
// while(true) {multiple enqueues and dequeues}

// / Automata build testing
// ab
// abcde
// ab*
// (ab)*
// a|b
// (a|b)*|de
// (a*|b*)|de + manual check via debugger if ending nodes( ones where next == nullptr) are in the ending list
// ((a.b*(cd)*)|de*)|(a.d)* + same as above
// (a||\\s)*|(\\\\|\\d)(\\\\\\a) -> printed error and stopped program => great
// \\\\\\\\\\\\
// \\e
// ((a.b)*|de)|\\ea
// \\e\\d\\a|\\s\\\\

// / ss::decapitalize_char()
// ((a.B*(cd)*)|de*)|(a.d)*

// / Automata working test
// \\a*\\s\\d* with string abc 69
// tested the work of the Automata for memory leaks with while(true)
//
// / test with files
// a*
// \\a*
// \\a*|\\d*
// a(b*cd)|ef
// ""
// \\ea\\e -> everything that has at least one "a"