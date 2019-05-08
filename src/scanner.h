#include <fstream>
#include "token.h"
#include "token_type.h"
#include "source.h"

#ifndef SCANNER_H
#define SCANNER_H

using namespace std;

class Scanner
{

private:
    Source& source;
    static TokenType alphanum_token_type(const string& keyword);
    Token get_token();

public:
    explicit Scanner(Source& s);
    void process_file();
};

#endif
