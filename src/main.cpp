#include <iostream>
#include <fstream>
#include <ctype.h>
#include "lexer.h"
#include "source.h"
#include "parser.h"
#include "interpreter.h"
#include <string>

using namespace std;

int main(){

	string filename;
	cout << "File name: ";
	cin >> filename;

	Source source_file(filename);
	Lexer lexer(source_file);
	Parser parser(lexer);
    Interpreter interpreter(parser);
    interpreter.execute();

	return 0;
}
