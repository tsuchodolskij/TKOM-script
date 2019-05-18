#include <string>
#include <fstream>

#ifndef SOURCE_H
#define SOURCE_H

using namespace std;

class Source
{

private:
    ifstream f;
    char current_char{};
    unsigned int line{};
    unsigned int column{};

public:
    explicit Source(const string& filename);
    ~Source();
    char get_current_char();
    unsigned int get_line();
    unsigned int get_column();
    void consume_char();
};

#endif
