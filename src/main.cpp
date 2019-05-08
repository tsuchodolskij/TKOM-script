#include <iostream>
#include <fstream>
#include <ctype.h>
#include "scanner.h"
#include "source.h"
#include <string>

using namespace std;

int main(){

	string filename;
	cout << "File name: ";
	cin >> filename;

	Source source_file(filename);
	Scanner scanner(source_file);
	scanner.process_file();

	return 0;
}
