#include <iostream>
#include <fstream>
#include <ctype.h>
#include "lexer.h"
#include "source.h"
#include "parser.h"
#include <string>

using namespace std;

int main(){

	string filename;
	cout << "File name: ";
	cin >> filename;

	Source source_file(filename);
	Lexer lexer(source_file);
	Parser parser(lexer);
    ProgramNode* node = parser.program();
    node->to_string("");

	return 0;
}
