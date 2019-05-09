#include <iostream>
#include <fstream>
#include <ctype.h>
#include "lexer.h"
#include "source.h"
#include <string>

using namespace std;

int main(){

	string filename;
	cout << "File name: ";
	cin >> filename;

	Source source_file(filename);
	Lexer lexer(source_file);
	lexer.process_file();

	return 0;
}
